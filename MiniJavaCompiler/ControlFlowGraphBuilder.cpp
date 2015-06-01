#include "ControlFlowGraphBuilder.h"

namespace RegisterAllocation {

    CControlFlowVertex::CControlFlowVertex( const CodeGeneration::IInstruction* instr ) : instruction( instr ) {

        const Temp::CTempList* definedVars = instr->DefinedVariables();
        while( definedVars != NULL && definedVars->GetHead() != NULL ) {
            defs.insert( *( definedVars->GetHead() ) );
            definedVars = definedVars->GetTail();
        }

        const Temp::CTempList* usesVars = instr->UsedVariables();
        while( usesVars != NULL && usesVars->GetHead() != NULL ) {
            uses.insert( *( usesVars->GetHead() ) );
            usesVars = usesVars->GetTail();
        }

        isMove = ( dynamic_cast< const CodeGeneration::MOVE* > ( instr ) != 0 );
    }


    void CControlFlowGraphBuilder::Build( const CodeGeneration::TInstructionsList& instructions ) {

        // Добавляем вершины
        AddInsructions( instructions );

        bool isChanging = false;

        std::vector<CControlFlowVertex*> vertices;

        vertices = controlFlowGraph.GetVertices();

        do {
            isChanging = false;

            for( auto vertex : vertices ) {
                if( UpdateLiveInOut( vertex ) ){
                    isChanging = true;
                }
            }
        } while( isChanging );
    }

    void CControlFlowGraphBuilder::AddInsructions( const CodeGeneration::TInstructionsList& instructions ) {

        std::unordered_map<Temp::CLabel, CControlFlowVertex*> labels;
        std::vector<CControlFlowVertex*> notLabels;

        CControlFlowVertex* prevVertex = NULL;

        for( const auto& instruction : instructions ) {
            auto vertex = new CControlFlowVertex( instruction );
            controlFlowGraph.AddVertex( vertex );

            if( prevVertex != NULL ) {
                controlFlowGraph.AddEdge( prevVertex, vertex );
            }

            const CodeGeneration::LABEL* instrAsLabel = dynamic_cast < const CodeGeneration::LABEL* >( vertex->instruction );
            if( instrAsLabel != 0 ) {
                assert( instrAsLabel->JumpTargets()->GetTail() == NULL );
                labels.insert( std::make_pair( *( instrAsLabel->JumpTargets()->GetHead() ), vertex ) );
            }
            else {
                notLabels.push_back( vertex );
            }
        }

        for( auto& vertex : notLabels ) {
            const Temp::CLabelList* labelList = vertex->instruction->JumpTargets();
            while( labelList->GetHead() != NULL ) {
                auto it = labels.find( *(labelList->GetHead()) );
                if( it != labels.end() ){
                    if( !controlFlowGraph.HasEdge( vertex, it->second ) ) {
                        controlFlowGraph.AddEdge( vertex, it->second );
                    }
                }
                labelList = labelList->GetTail();
            }
        }
    }

    bool CControlFlowGraphBuilder::UpdateLiveInOut( CControlFlowVertex* vertex ) {

        std::unordered_set<Temp::CTemp> oldLiveIn( vertex->liveIn );
        std::unordered_set<Temp::CTemp> oldLiveOut( vertex->liveOut );

        // in[n] <- use[n] U ( out[n] - def[n] )
        vertex->liveIn.insert( vertex->uses.begin(), vertex->uses.end() );
        for( const auto& out : vertex->liveOut ) {
            if( vertex->defs.find( out ) == vertex->defs.end() ) {
                vertex->liveIn.insert( out );
            }
        }

        // out[n] <- U_{s in succ[n]} in[s]
        auto successors = controlFlowGraph.GetListOut( vertex );
        for( const auto& succ : successors ) {
            vertex->liveOut.insert( succ->liveIn.begin(), succ->liveIn.end() );
        }

        // Проверяем изменения
        if( vertex->liveIn != oldLiveIn || vertex->liveOut != oldLiveOut ) {
            return true;
        }

        return false;
    }

    bool CControlFlowVertex::operator==( const CControlFlowVertex& other ) const {
        return instruction == other.instruction;
    }

}