#ifndef UUID1764110257168
#define UUID1764110257168

/**
  * RandomForestClassifier(base_estimator=deprecated, bootstrap=True, ccp_alpha=0.0, class_name=RandomForestClassifier, class_weight=None, criterion=gini, estimator=DecisionTreeClassifier(), estimator_params=('criterion', 'max_depth', 'min_samples_split', 'min_samples_leaf', 'min_weight_fraction_leaf', 'max_features', 'max_leaf_nodes', 'min_impurity_decrease', 'random_state', 'ccp_alpha'), max_depth=20, max_features=sqrt, max_leaf_nodes=None, max_samples=None, min_impurity_decrease=0.0, min_samples_leaf=1, min_samples_split=2, min_weight_fraction_leaf=0.0, n_estimators=20, n_jobs=None, num_outputs=5, oob_score=False, package_name=everywhereml.sklearn.ensemble, random_state=None, template_folder=everywhereml/sklearn/ensemble, verbose=0, warm_start=False)
 */
class RandomForestClassifier {
    public:

        /**
         * Predict class from features
         */
        int predict(float *x) {
            int predictedValue = 0;
            size_t startedAt = micros();

            
                    
            uint16_t votes[5] = { 0 };
            uint8_t classIdx = 0;
            float classScore = 0;

            
                tree0(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree1(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree2(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree3(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree4(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree5(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree6(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree7(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree8(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree9(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree10(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree11(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree12(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree13(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree14(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree15(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree16(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree17(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree18(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree19(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            

            // return argmax of votes
            uint8_t maxClassIdx = 0;
            float maxVote = votes[0];

            for (uint8_t i = 1; i < 5; i++) {
                if (votes[i] > maxVote) {
                    maxClassIdx = i;
                    maxVote = votes[i];
                }
            }

            predictedValue = maxClassIdx;

                    

            latency = micros() - startedAt;

            return (lastPrediction = predictedValue);
        }

        
            

            /**
             * Predict class label
             */
            String predictLabel(float *x) {
                return getLabelOf(predict(x));
            }

            /**
             * Get label of last prediction
             */
            String getLabel() {
                return getLabelOf(lastPrediction);
            }

            /**
             * Get label of given class
             */
            String getLabelOf(int8_t idx) {
                switch (idx) {
                    case -1:
                        return "ERROR";
                    
                        case 0:
                            return "neutral";
                    
                        case 1:
                            return "clockwise";
                    
                        case 2:
                            return "counterclockwise";
                    
                        case 3:
                            return "vertical_shake";
                    
                        case 4:
                            return "horizontal_shake";
                    
                    default:
                        return "UNKNOWN";
                }
            }


            /**
             * Get latency in micros
             */
            uint32_t latencyInMicros() {
                return latency;
            }

            /**
             * Get latency in millis
             */
            uint16_t latencyInMillis() {
                return latency / 1000;
            }
            

    protected:
        float latency = 0;
        int lastPrediction = 0;

        
            

        
            
                /**
                 * Random forest's tree #0
                 */
                void tree0(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[86] < 0.026886528357863426) {
                            
                                
                        if (x[38] < 0.5789024829864502) {
                            
                                
                        *classIdx = 0;
                        *classScore = 80.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[101] < 0.26761650294065475) {
                            
                                
                        *classIdx = 3;
                        *classScore = 61.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[62] < 0.710754930973053) {
                            
                                
                        if (x[59] < 0.21328503638505936) {
                            
                                
                        *classIdx = 2;
                        *classScore = 74.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 70.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 70.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 80.0;
                        return;

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #1
                 */
                void tree1(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[62] < 0.471208855509758) {
                            
                                
                        if (x[46] < 0.003335517249070108) {
                            
                                
                        *classIdx = 0;
                        *classScore = 80.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 85.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[44] < 0.5906972885131836) {
                            
                                
                        if (x[49] < 0.004860728862695396) {
                            
                                
                        *classIdx = 2;
                        *classScore = 62.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[108] < 0.03334190882742405) {
                            
                                
                        *classIdx = 1;
                        *classScore = 85.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 62.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[8] < 0.1375129371881485) {
                            
                                
                        if (x[100] < 0.7968145906925201) {
                            
                                
                        *classIdx = 2;
                        *classScore = 62.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 63.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 75.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #2
                 */
                void tree2(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[49] < 0.007554893847554922) {
                            
                                
                        if (x[108] < 0.16892052814364433) {
                            
                                
                        if (x[45] < 0.3777848184108734) {
                            
                                
                        *classIdx = 2;
                        *classScore = 76.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 62.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 76.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[42] < 0.7750511467456818) {
                            
                                
                        *classIdx = 1;
                        *classScore = 81.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[89] < 0.02431991882622242) {
                            
                                
                        *classIdx = 2;
                        *classScore = 76.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 70.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #3
                 */
                void tree3(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[108] < 0.22599955648183823) {
                            
                                
                        if (x[46] < 0.0014791431021876633) {
                            
                                
                        *classIdx = 0;
                        *classScore = 73.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[48] < 0.07269875891506672) {
                            
                                
                        if (x[79] < 0.03219290578272194) {
                            
                                
                        *classIdx = 0;
                        *classScore = 73.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 78.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[40] < 0.7464212775230408) {
                            
                                
                        *classIdx = 1;
                        *classScore = 67.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[24] < 0.3633241802453995) {
                            
                                
                        *classIdx = 2;
                        *classScore = 78.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 64.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 83.0;
                        return;

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #4
                 */
                void tree4(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[48] < 0.07876929268240929) {
                            
                                
                        if (x[45] < 0.36931511759757996) {
                            
                                
                        *classIdx = 2;
                        *classScore = 84.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[23] < 0.26615646481513977) {
                            
                                
                        *classIdx = 3;
                        *classScore = 75.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 62.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[88] < 0.1552368775010109) {
                            
                                
                        if (x[108] < 0.0333698894828558) {
                            
                                
                        *classIdx = 1;
                        *classScore = 70.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 84.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 74.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #5
                 */
                void tree5(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[82] < 0.7082917392253876) {
                            
                                
                        if (x[29] < 0.019762189127504826) {
                            
                                
                        if (x[20] < 0.42602039873600006) {
                            
                                
                        *classIdx = 0;
                        *classScore = 66.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[4] < 0.5507798790931702) {
                            
                                
                        if (x[0] < 0.6497695744037628) {
                            
                                
                        *classIdx = 2;
                        *classScore = 77.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 86.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[82] < 0.6364977657794952) {
                            
                                
                        *classIdx = 1;
                        *classScore = 58.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 78.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[67] < 0.00048880201211432) {
                            
                                
                        *classIdx = 3;
                        *classScore = 86.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 58.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[7] < 0.000725851277820766) {
                            
                                
                        *classIdx = 2;
                        *classScore = 77.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 78.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #6
                 */
                void tree6(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[82] < 0.7082917392253876) {
                            
                                
                        if (x[59] < 0.1299450919032097) {
                            
                                
                        if (x[23] < 0.31122449040412903) {
                            
                                
                        if (x[78] < 2.1603612899780273) {
                            
                                
                        *classIdx = 3;
                        *classScore = 68.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 75.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 69.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 74.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 79.0;
                        return;

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #7
                 */
                void tree7(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[67] < 2.786348929362248e-06) {
                            
                                
                        *classIdx = 0;
                        *classScore = 78.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[9] < 0.01717327069491148) {
                            
                                
                        if (x[41] < 0.36912065744400024) {
                            
                                
                        *classIdx = 1;
                        *classScore = 60.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[40] < 0.6595091819763184) {
                            
                                
                        *classIdx = 2;
                        *classScore = 76.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[36] < 0.5) {
                            
                                
                        *classIdx = 2;
                        *classScore = 76.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 71.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 80.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #8
                 */
                void tree8(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[19] < 0.23793750256299973) {
                            
                                
                        if (x[79] < 0.013688607607036829) {
                            
                                
                        *classIdx = 0;
                        *classScore = 78.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[100] < 0.7965802252292633) {
                            
                                
                        if (x[79] < 0.2122071087360382) {
                            
                                
                        if (x[23] < 0.29591837525367737) {
                            
                                
                        if (x[3] < 0.5000000149011612) {
                            
                                
                        *classIdx = 2;
                        *classScore = 74.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 66.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 66.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[2] < 0.5875575840473175) {
                            
                                
                        *classIdx = 2;
                        *classScore = 74.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 66.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 70.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 77.0;
                        return;

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #9
                 */
                void tree9(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[82] < 0.7082917392253876) {
                            
                                
                        if (x[100] < 0.7965802252292633) {
                            
                                
                        if (x[48] < 0.06822502799332142) {
                            
                                
                        if (x[62] < 0.4826185256242752) {
                            
                                
                        *classIdx = 0;
                        *classScore = 64.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 82.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 71.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 72.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 76.0;
                        return;

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #10
                 */
                void tree10(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[106] < 0.022414172999560833) {
                            
                                
                        if (x[46] < 0.001459288818296045) {
                            
                                
                        *classIdx = 0;
                        *classScore = 85.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[7] < 0.0006509054219350219) {
                            
                                
                        if (x[41] < 0.3844580799341202) {
                            
                                
                        if (x[85] < 0.18551789969205856) {
                            
                                
                        *classIdx = 2;
                        *classScore = 63.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 64.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[3] < 0.5138248950242996) {
                            
                                
                        *classIdx = 2;
                        *classScore = 63.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 85.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[23] < 0.09948979504406452) {
                            
                                
                        *classIdx = 1;
                        *classScore = 64.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 70.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[81] < 0.15982762351632118) {
                            
                                
                        *classIdx = 4;
                        *classScore = 70.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 83.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #11
                 */
                void tree11(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[66] < 0.0009695512562757358) {
                            
                                
                        *classIdx = 0;
                        *classScore = 74.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[100] < 0.7965802252292633) {
                            
                                
                        if (x[87] < 0.0006513057451229542) {
                            
                                
                        if (x[59] < 0.11792121455073357) {
                            
                                
                        *classIdx = 2;
                        *classScore = 70.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 74.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 71.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[110] < 44.5) {
                            
                                
                        *classIdx = 4;
                        *classScore = 71.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 76.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #12
                 */
                void tree12(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[19] < 0.23793750256299973) {
                            
                                
                        if (x[79] < 0.013816558755934238) {
                            
                                
                        *classIdx = 0;
                        *classScore = 83.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[106] < 0.017568526789546013) {
                            
                                
                        if (x[59] < 0.1371738277375698) {
                            
                                
                        *classIdx = 2;
                        *classScore = 67.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 0.7672810852527618) {
                            
                                
                        *classIdx = 1;
                        *classScore = 74.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 67.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 70.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 71.0;
                        return;

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #13
                 */
                void tree13(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[48] < 0.07156384736299515) {
                            
                                
                        if (x[78] < 2.1535836458206177) {
                            
                                
                        if (x[6] < 0.008433626964688301) {
                            
                                
                        if (x[41] < 0.5746421217918396) {
                            
                                
                        *classIdx = 2;
                        *classScore = 78.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 66.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 68.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 78.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[29] < 0.0039880197728052735) {
                            
                                
                        *classIdx = 4;
                        *classScore = 74.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[108] < 0.06833641603589058) {
                            
                                
                        *classIdx = 1;
                        *classScore = 79.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 74.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #14
                 */
                void tree14(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[83] < 0.21081792563199997) {
                            
                                
                        *classIdx = 4;
                        *classScore = 83.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[3] < 0.460829496383667) {
                            
                                
                        if (x[103] < 0.26725518703460693) {
                            
                                
                        *classIdx = 3;
                        *classScore = 80.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 75.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[58] < 0.5490919947624207) {
                            
                                
                        if (x[53] < 96.0) {
                            
                                
                        *classIdx = 0;
                        *classScore = 56.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 75.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 71.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #15
                 */
                void tree15(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[105] < 0.2574847936630249) {
                            
                                
                        if (x[26] < 0.002328115690033883) {
                            
                                
                        *classIdx = 0;
                        *classScore = 67.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 0.6059907972812653) {
                            
                                
                        if (x[39] < 0.42620910704135895) {
                            
                                
                        *classIdx = 2;
                        *classScore = 80.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 81.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[42] < 0.7310838401317596) {
                            
                                
                        *classIdx = 1;
                        *classScore = 71.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[0] < 0.6981566846370697) {
                            
                                
                        *classIdx = 2;
                        *classScore = 80.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 66.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[118] < 2.6410549879074097) {
                            
                                
                        *classIdx = 3;
                        *classScore = 81.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[20] < 0.6794217824935913) {
                            
                                
                        *classIdx = 2;
                        *classScore = 80.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 66.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #16
                 */
                void tree16(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[69] < 0.0015533924452029169) {
                            
                                
                        if (x[109] < 0.052425654605031013) {
                            
                                
                        if (x[79] < 0.016477874480187893) {
                            
                                
                        *classIdx = 0;
                        *classScore = 71.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[106] < 0.0032636771793477237) {
                            
                                
                        *classIdx = 2;
                        *classScore = 67.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 70.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 73.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[4] < 0.5436237156391144) {
                            
                                
                        if (x[108] < 0.1960771083831787) {
                            
                                
                        *classIdx = 2;
                        *classScore = 67.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 73.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 84.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #17
                 */
                void tree17(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[63] < 0.45565101504325867) {
                            
                                
                        if (x[48] < 0.07623573392629623) {
                            
                                
                        if (x[106] < 0.017568526789546013) {
                            
                                
                        *classIdx = 2;
                        *classScore = 79.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 63.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[0] < 0.739631325006485) {
                            
                                
                        *classIdx = 1;
                        *classScore = 65.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[18] < 3.1946033239364624) {
                            
                                
                        *classIdx = 4;
                        *classScore = 79.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 79.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 79.0;
                        return;

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #18
                 */
                void tree18(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[27] < 1.0754913319033221e-05) {
                            
                                
                        *classIdx = 0;
                        *classScore = 82.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[1] < 0.460829496383667) {
                            
                                
                        if (x[106] < 0.021947148256003857) {
                            
                                
                        if (x[29] < 0.003993374411948025) {
                            
                                
                        *classIdx = 4;
                        *classScore = 61.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[88] < 0.19818511605262756) {
                            
                                
                        *classIdx = 2;
                        *classScore = 77.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 61.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 3;
                        *classScore = 67.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 78.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #19
                 */
                void tree19(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[45] < 0.36931511759757996) {
                            
                                
                        if (x[5] < 0.306473046541214) {
                            
                                
                        *classIdx = 2;
                        *classScore = 66.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 75.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[100] < 0.814938873052597) {
                            
                                
                        if (x[7] < 0.00043565510623011505) {
                            
                                
                        *classIdx = 0;
                        *classScore = 73.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 73.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[46] < 0.020936327055096626) {
                            
                                
                        *classIdx = 3;
                        *classScore = 78.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 4;
                        *classScore = 73.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        


            
};



static RandomForestClassifier forest;


#endif