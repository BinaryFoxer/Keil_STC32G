/*
 * PID Controller Implementation in C
 * 
 * Created by Joshua Saxby (aka @saxbophone) on 1 Jan, 2016
 * 
 * My own attempt at implementing the PID algorithm in some (hopefully) clean, understandable C.
 *
 * See LICENSE for licensing details.
 */

// protection against multiple includes
#ifndef SAXBOPHONE_PID_H
#define SAXBOPHONE_PID_H

#ifdef __cplusplus
extern "C"{
#endif

// PID����
    typedef struct pid_calibration {
        /*
         * struct PID_Calibration
         * 
         * Struct storing calibrated PID constants for a PID Controller
         * These are used for tuning the algorithm and the values they take are
         * dependent upon the application - (in other words, YMMV...)
         */
        float kp; // Proportional gain
        float ki; // Integral gain
        float kd; // Derivative gain
    } PID_Calibration;

// PID��ǰ״̬������ֵ
    typedef struct pid_state {
        /*
         * struct PID_State
         * 
         * Struct storing the current state of a PID Controller.
         * This is used as the input value to the PID algorithm function, which also
         * returns a PID_State struct reflecting the adjustments suggested by the algorithm.
         * 
         * NOTE: The output field in this struct is set by the PID algorithm function, and
         * is ignored in the actual calculations.
         */
        unsigned int actual; // ��������ʵֵ
        unsigned int target; // Ŀ��ֵ
        unsigned int time_delta; // Time since last sample/calculation - should be set when updating state
								//����ʱ��������msΪ��λ
        unsigned int previous_error;	// The previously calculated error between actual and target (zero initially)
        unsigned int integral; // Sum of integral error over time
        unsigned int output; // the modified output value calculated by the algorithm, to compensate for error
    } PID_State;


    /*
     * PID Controller Algorithm implementation
     * 
     * Given a PID calibration for the P, I and D values and a PID_State for the current
     * state of the PID controller, calculate the new state for the PID Controller and set
     * the output state to compensate for any error as defined by the algorithm
     */
    PID_State* pid_iterate(PID_Calibration * calibration, PID_State * state);


#ifdef __cplusplus
} // extern "C"
#endif

// end of header
#endif
