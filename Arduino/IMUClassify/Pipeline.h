#ifndef UUID1380823444560
#define UUID1380823444560

#include <cstring>


namespace ContinousMotionPipeline {

    
        #ifndef UUID1378773095440
#define UUID1378773095440

/**
  * MinMaxScaler(low=0, high=1)
 */
class Step0 {
    public:

        /**
         * Transform input vector
         */
        bool transform(float *x) {
            
    for (uint16_t i = 0; i < 6; i++) {
        x[i] = (x[i] - offset[i]) * scale[i] + 0;

        if (x[i] < 0) x[i] = 0;
        else if (x[i] > 1) x[i] = 1;
    }

    return true;


            return true;
        }

    protected:
        
    float offset[6] = {-1.78000000000f, -2.68000000000f, -4.00000000000f, -980.35000000000f, -336.43000000000f, -471.92000000000f};
    float scale[6] = {0.30864197531f, 0.14970059880f, 0.16891891892f, 0.00038965846f, 0.00163625951f, 0.00128070490f};

};



#endif
    
        #ifndef UUID1378752656144
#define UUID1378752656144

/**
  * Window(length=104, shift=31)
 */
class Step1 {
    public:

        /**
         * Transform input vector
         */
        bool transform(float *x) {
            
    // append x to queue
    memcpy(queue + head, x, sizeof(float) * 6);
    head += 6;

    if (head != 624)
        return false;

    // copy queue to x and shift
    memcpy(x, queue, sizeof(float) * 624);

    
        memcpy(queue, queue + 186, sizeof(float) * 438);
    

    head -= 186;



            return true;
        }

    protected:
        
    uint16_t head = 0;
    float queue[624] = {0};

};



#endif
    
        #ifndef UUID1378747900368
#define UUID1378747900368

/**
  * SpectralFeatures(num_inputs=6, window_length=104, order=2, num_features=20)
 */
class Step2 {
    public:

        /**
         * Transform input vector
         */
        bool transform(float *x) {
            
    // spectral features
    uint16_t idx = 0;

    for (uint16_t k = 0; k < 6; k++) {
        float minimum = 9999999;
        float maximum = -9999999;
        float abs_minimum = 999999;
        float abs_maximum = 0;
        float mean = 0;
        float abs_energy = 0;
        float mean_abs_change = 0;
        float cid_ce = 0;
        float xi_prev = x[k];

        // first-order features
        for (uint16_t i = k; i < 624; i += 6) {
            float xi = x[i];
            float abs_xi = abs(xi);
            float xi_prev2 = (i >= k + 12) ? x[i - 12] : xi;

            float xi2 = xi * xi;
            float diff = xi - xi_prev;

            // start of features
            minimum = xi < minimum ? xi : minimum;
            maximum = xi > maximum ? xi : maximum;
            abs_minimum = abs_xi < abs_minimum ? abs_xi : abs_minimum;
            abs_maximum = abs_xi > abs_maximum ? abs_xi : abs_maximum;
            mean += xi;
            abs_energy += xi2;
            mean_abs_change += abs(diff);
            cid_ce += diff * diff;
            xi_prev = xi;
        }

        mean /= 104;
        abs_energy /= 104;
        mean_abs_change /= 104;
        cid_ce /= 104;

        buffer[idx++] = maximum;
        buffer[idx++] = minimum;
        buffer[idx++] = abs_maximum;
        buffer[idx++] = abs_minimum;
        buffer[idx++] = mean;
        buffer[idx++] = abs_energy;
        buffer[idx++] = mean_abs_change;
        buffer[idx++] = cid_ce;

        
            // second-order features
            float xi_mean_prev = x[k] - mean;
            float count_above_mean = 0;
            float count_below_mean = 0;
            float first_position_of_max = 624;
            float first_position_of_min = 624;
            float max_count = 0;
            float min_count = 0;
            float max_thresh = maximum - abs(maximum) * 0.02;
            float min_thresh = minimum + abs(minimum) * 0.02;
            float var = 0;
            float std = 0;
            float kurtosis = 0;
            float skew = 0;
            float has_large_std = 0;
            float variation_coefficient = 0;

            for (uint16_t i = k; i < 624; i += 6) {
                float xi = x[i];
                float xi_mean = xi - mean;
                float var_i = xi_mean * xi_mean;

                // start of features
                var += var_i;
                count_above_mean += xi_mean >  0.001 ? 1 : 0;
                count_below_mean += xi_mean < -0.001 ? 1 : 0;
                first_position_of_max = (i < first_position_of_max && abs(xi - maximum) < 0.001) ? i : first_position_of_max;
                first_position_of_min = (i < first_position_of_min && abs(xi - minimum) < 0.001) ? i : first_position_of_min;

                if (var_i > 0.001) {
                    skew += var_i * xi_mean;
                    kurtosis += var_i * var_i;
                }
                if (xi > max_thresh) { max_count += 1; }
                if (xi < min_thresh) { min_count += 1; }

                xi_mean_prev = xi_mean;
            }

            var /= 104;
            std = sqrt(var);
            first_position_of_max = int((first_position_of_max - k) / 104);
            first_position_of_min = int((first_position_of_min - k) / 104);
            skew = var > 0.001 ? skew / pow(var, 1.5) : 0;
            kurtosis = var > 0.001 ? kurtosis / (var * var) : 0;
            has_large_std = std > 0.25 * (maximum - minimum);
            variation_coefficient = (mean > 0.001) ? var / mean : 0;

            buffer[idx++] = std;
            buffer[idx++] = var;
            buffer[idx++] = count_above_mean;
            buffer[idx++] = count_below_mean;
            buffer[idx++] = first_position_of_max;
            buffer[idx++] = first_position_of_min;
            buffer[idx++] = max_count;
            buffer[idx++] = min_count;
            buffer[idx++] = has_large_std;
            buffer[idx++] = skew;
            buffer[idx++] = kurtosis;
            buffer[idx++] = variation_coefficient;
        
    }

    memcpy(x, buffer, 120 * sizeof(float));


            return true;
        }

    protected:
        
    float buffer[120];

};



#endif
    

     /**
      * Pipeline:
 * ---------
 *  > MinMaxScaler(low=0, high=1)
 *  > Window(length=104, shift=31)
 *  > SpectralFeatures(num_inputs=6, window_length=104, order=2, num_features=20)
     */
    class Pipeline {
        public:
            static const uint16_t NUM_INPUTS = 6;
            static const uint16_t NUM_OUTPUTS = 120;
            static const uint16_t WORKING_SIZE = 624;
            float X[624];

            /**
             * Apply pipeline to input vector
             */
            template<typename T>
            bool transform(T *x) {
                for (uint16_t i = 0; i < 6; i++)
                    this->X[i] = x[i];

                size_t start = micros();
                bool isOk =
                
					step0.transform(X)
					
					&& step1.transform(X)
					
					&& step2.transform(X)
                ;

                latency = micros() - start;

                return isOk;
            }

            /**
             * Debug output feature vector
             */
            template<typename PrinterInterface>
            void debugTo(PrinterInterface &printer, uint8_t precision=5) {
                printer.print(X[0], precision);

                for (uint16_t i = 1; i < 120; i++) {
                    printer.print(", ");
                    printer.print(X[i], precision);
                }

                printer.print('\n');
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
            float latency;
            
                ContinousMotionPipeline::Step0 step0;
            
                ContinousMotionPipeline::Step1 step1;
            
                ContinousMotionPipeline::Step2 step2;
            
    };
}


static ContinousMotionPipeline::Pipeline pipeline;


#endif