/*
 * P1p3.c
 *
 * Code generation for model "P1p3".
 *
 * Model version              : 1.88
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Fri Sep 28 11:48:56 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "P1p3.h"
#include "P1p3_private.h"
#include "P1p3_dt.h"

/* Block signals (auto storage) */
B_P1p3_T P1p3_B;

/* Continuous states */
X_P1p3_T P1p3_X;

/* Block states (auto storage) */
DW_P1p3_T P1p3_DW;

/* Real-time model */
RT_MODEL_P1p3_T P1p3_M_;
RT_MODEL_P1p3_T *const P1p3_M = &P1p3_M_;
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(P1p3_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(P1p3_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (P1p3_M->Timing.TaskCounters.TID[1] == 0) {
    P1p3_M->Timing.RateInteraction.TID1_2 = (P1p3_M->Timing.TaskCounters.TID[2] ==
      0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    P1p3_M->Timing.perTaskSampleHits[5] = P1p3_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (P1p3_M->Timing.TaskCounters.TID[2])++;
  if ((P1p3_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    P1p3_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  P1p3_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void P1p3_output0(void)                /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_FrontmotorSaturation;
  real_T rtb_BackmotorSaturation;
  real_T rtb_Add;
  if (rtmIsMajorTimeStep(P1p3_M)) {
    /* set solver stop time */
    if (!(P1p3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&P1p3_M->solverInfo, ((P1p3_M->Timing.clockTickH0 +
        1) * P1p3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&P1p3_M->solverInfo, ((P1p3_M->Timing.clockTick0 + 1)
        * P1p3_M->Timing.stepSize0 + P1p3_M->Timing.clockTickH0 *
        P1p3_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(P1p3_M)) {
    P1p3_M->Timing.t[0] = rtsiGetT(&P1p3_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(P1p3_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

    /* S-Function Block: P1p3/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(P1p3_DW.HILReadEncoderTimebase_Task, 1,
        &P1p3_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 = P1p3_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 = P1p3_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_FrontmotorSaturation = P1p3_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* RateTransition: '<S3>/Rate Transition: y' */
    if (P1p3_M->Timing.RateInteraction.TID1_2) {
      P1p3_B.RateTransitiony = P1p3_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S3>/Rate Transition: y' */

    /* DeadZone: '<S3>/Dead Zone: y' */
    if (P1p3_B.RateTransitiony > P1p3_P.DeadZoney_End) {
      rtb_BackmotorSaturation = P1p3_B.RateTransitiony - P1p3_P.DeadZoney_End;
    } else if (P1p3_B.RateTransitiony >= P1p3_P.DeadZoney_Start) {
      rtb_BackmotorSaturation = 0.0;
    } else {
      rtb_BackmotorSaturation = P1p3_B.RateTransitiony - P1p3_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: y' */

    /* Gain: '<S3>/Joystick_gain_y' incorporates:
     *  Gain: '<S3>/Gain: y'
     */
    P1p3_B.Joystick_gain_y = P1p3_P.Gainy_Gain * rtb_BackmotorSaturation *
      P1p3_P.Joystick_gain_y;

    /* Gain: '<S2>/Elevation: Count to rad' */
    P1p3_B.ElevationCounttorad = P1p3_P.ElevationCounttorad_Gain *
      rtb_FrontmotorSaturation;

    /* Gain: '<S4>/Gain' */
    P1p3_B.Gain = P1p3_P.Gain_Gain * P1p3_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/offset_e'
     */
    P1p3_B.Sum1 = P1p3_B.Gain + P1p3_P.offset_e_Value;

    /* RateTransition: '<S3>/Rate Transition: x' */
    if (P1p3_M->Timing.RateInteraction.TID1_2) {
      P1p3_B.RateTransitionx = P1p3_DW.RateTransitionx_Buffer0;
    }

    /* End of RateTransition: '<S3>/Rate Transition: x' */

    /* DeadZone: '<S3>/Dead Zone: x' */
    if (P1p3_B.RateTransitionx > P1p3_P.DeadZonex_End) {
      rtb_BackmotorSaturation = P1p3_B.RateTransitionx - P1p3_P.DeadZonex_End;
    } else if (P1p3_B.RateTransitionx >= P1p3_P.DeadZonex_Start) {
      rtb_BackmotorSaturation = 0.0;
    } else {
      rtb_BackmotorSaturation = P1p3_B.RateTransitionx - P1p3_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: x' */

    /* Gain: '<S3>/Joystick_gain_x' incorporates:
     *  Gain: '<S3>/Gain: x'
     */
    P1p3_B.Joystick_gain_x = P1p3_P.Gainx_Gain * rtb_BackmotorSaturation *
      P1p3_P.Joystick_gain_x;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/Vs_const'
     */
    rtb_BackmotorSaturation = P1p3_B.Joystick_gain_y + P1p3_P.V_s;

    /* Sum: '<S1>/Add' */
    rtb_Add = P1p3_B.Joystick_gain_x + rtb_BackmotorSaturation;

    /* Gain: '<S1>/Back gain' incorporates:
     *  Sum: '<S1>/Subtract'
     */
    rtb_BackmotorSaturation = (rtb_BackmotorSaturation - P1p3_B.Joystick_gain_x)
      * P1p3_P.Backgain_Gain;

    /* Gain: '<S1>/Front gain' */
    rtb_FrontmotorSaturation = P1p3_P.Frontgain_Gain * rtb_Add;
  }

  /* Gain: '<S5>/Gain' incorporates:
   *  TransferFcn: '<S2>/Elevation: Transfer Fcn'
   */
  P1p3_B.Gain_d = (P1p3_P.ElevationTransferFcn_C *
                   P1p3_X.ElevationTransferFcn_CSTATE +
                   P1p3_P.ElevationTransferFcn_D * P1p3_B.ElevationCounttorad) *
    P1p3_P.Gain_Gain_n;
  if (rtmIsMajorTimeStep(P1p3_M)) {
    /* Gain: '<S2>/Pitch: Count to rad' */
    P1p3_B.PitchCounttorad = P1p3_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S6>/Gain' */
    P1p3_B.Gain_i = P1p3_P.Gain_Gain_a * P1p3_B.PitchCounttorad;
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  TransferFcn: '<S2>/Pitch: Transfer Fcn'
   */
  P1p3_B.Gain_b = (P1p3_P.PitchTransferFcn_C * P1p3_X.PitchTransferFcn_CSTATE +
                   P1p3_P.PitchTransferFcn_D * P1p3_B.PitchCounttorad) *
    P1p3_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(P1p3_M)) {
    /* Gain: '<S2>/Travel: Count to rad' */
    P1p3_B.TravelCounttorad = P1p3_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S2>/Travel: Transfer Fcn'
   */
  P1p3_B.Gain_dc = (P1p3_P.TravelTransferFcn_C * P1p3_X.TravelTransferFcn_CSTATE
                    + P1p3_P.TravelTransferFcn_D * P1p3_B.TravelCounttorad) *
    P1p3_P.Gain_Gain_l;
  if (rtmIsMajorTimeStep(P1p3_M)) {
    /* Gain: '<S8>/Gain' */
    P1p3_B.Gain_p = P1p3_P.Gain_Gain_ar * P1p3_B.TravelCounttorad;

    /* Saturate: '<S2>/Front motor: Saturation' */
    if (rtb_FrontmotorSaturation > P1p3_P.FrontmotorSaturation_UpperSat) {
      rtb_FrontmotorSaturation = P1p3_P.FrontmotorSaturation_UpperSat;
    } else {
      if (rtb_FrontmotorSaturation < P1p3_P.FrontmotorSaturation_LowerSat) {
        rtb_FrontmotorSaturation = P1p3_P.FrontmotorSaturation_LowerSat;
      }
    }

    /* End of Saturate: '<S2>/Front motor: Saturation' */

    /* Saturate: '<S2>/Back motor: Saturation' */
    if (rtb_BackmotorSaturation > P1p3_P.BackmotorSaturation_UpperSat) {
      rtb_BackmotorSaturation = P1p3_P.BackmotorSaturation_UpperSat;
    } else {
      if (rtb_BackmotorSaturation < P1p3_P.BackmotorSaturation_LowerSat) {
        rtb_BackmotorSaturation = P1p3_P.BackmotorSaturation_LowerSat;
      }
    }

    /* End of Saturate: '<S2>/Back motor: Saturation' */

    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: P1p3/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      P1p3_DW.HILWriteAnalog_Buffer[0] = rtb_FrontmotorSaturation;
      P1p3_DW.HILWriteAnalog_Buffer[1] = rtb_BackmotorSaturation;
      result = hil_write_analog(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILWriteAnalog_channels, 2, &P1p3_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
      }
    }
  }
}

/* Model update function for TID0 */
void P1p3_update0(void)                /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(P1p3_M)) {
    rt_ertODEUpdateContinuousStates(&P1p3_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P1p3_M->Timing.clockTick0)) {
    ++P1p3_M->Timing.clockTickH0;
  }

  P1p3_M->Timing.t[0] = rtsiGetSolverStopTime(&P1p3_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P1p3_M->Timing.clockTick1)) {
    ++P1p3_M->Timing.clockTickH1;
  }

  P1p3_M->Timing.t[1] = P1p3_M->Timing.clockTick1 * P1p3_M->Timing.stepSize1 +
    P1p3_M->Timing.clockTickH1 * P1p3_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void P1p3_derivatives(void)
{
  XDot_P1p3_T *_rtXdot;
  _rtXdot = ((XDot_P1p3_T *) P1p3_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += P1p3_P.ElevationTransferFcn_A *
    P1p3_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += P1p3_B.ElevationCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += P1p3_P.PitchTransferFcn_A *
    P1p3_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += P1p3_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += P1p3_P.TravelTransferFcn_A *
    P1p3_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += P1p3_B.TravelCounttorad;
}

/* Model output function for TID2 */
void P1p3_output2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: P1p3/Joystick/Game Controller (game_controller_block) */
  {
    if (P1p3_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(P1p3_DW.GameController_Controller, &state,
        &new_data);
      if (result == 0) {
        P1p3_B.GameController_o4 = state.x;
        P1p3_B.GameController_o5 = state.y;
      }
    } else {
      P1p3_B.GameController_o4 = 0;
      P1p3_B.GameController_o5 = 0;
    }
  }
}

/* Model update function for TID2 */
void P1p3_update2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* Update for RateTransition: '<S3>/Rate Transition: y' */
  P1p3_DW.RateTransitiony_Buffer0 = P1p3_B.GameController_o5;

  /* Update for RateTransition: '<S3>/Rate Transition: x' */
  P1p3_DW.RateTransitionx_Buffer0 = P1p3_B.GameController_o4;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P1p3_M->Timing.clockTick2)) {
    ++P1p3_M->Timing.clockTickH2;
  }

  P1p3_M->Timing.t[2] = P1p3_M->Timing.clockTick2 * P1p3_M->Timing.stepSize2 +
    P1p3_M->Timing.clockTickH2 * P1p3_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void P1p3_output(int_T tid)
{
  switch (tid) {
   case 0 :
    P1p3_output0();
    break;

   case 2 :
    P1p3_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void P1p3_update(int_T tid)
{
  switch (tid) {
   case 0 :
    P1p3_update0();
    break;

   case 2 :
    P1p3_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void P1p3_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: P1p3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &P1p3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P1p3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(P1p3_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P1p3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(P1p3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P1p3_M, _rt_error_message);
      return;
    }

    if ((P1p3_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (P1p3_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &P1p3_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = P1p3_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &P1p3_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = P1p3_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_analog_input_chan, 8U,
        &P1p3_DW.HILInitialize_AIMinimums[0], &P1p3_DW.HILInitialize_AIMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }

    if ((P1p3_P.HILInitialize_set_analog_output && !is_switching) ||
        (P1p3_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &P1p3_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = P1p3_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &P1p3_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = P1p3_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_analog_output_cha, 8U,
        &P1p3_DW.HILInitialize_AOMinimums[0], &P1p3_DW.HILInitialize_AOMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }

    if ((P1p3_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (P1p3_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P1p3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P1p3_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_analog_output_cha, 8U,
        &P1p3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }

    if (P1p3_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P1p3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P1p3_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (P1p3_DW.HILInitialize_Card, P1p3_P.HILInitialize_analog_output_cha, 8U,
         &P1p3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }

    if ((P1p3_P.HILInitialize_set_encoder_param && !is_switching) ||
        (P1p3_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &P1p3_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = P1p3_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_encoder_channels, 8U, (t_encoder_quadrature_mode *)
        &P1p3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }

    if ((P1p3_P.HILInitialize_set_encoder_count && !is_switching) ||
        (P1p3_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &P1p3_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = P1p3_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_encoder_channels, 8U,
        &P1p3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }

    if ((P1p3_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (P1p3_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &P1p3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = P1p3_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &P1p3_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          P1p3_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &P1p3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            P1p3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            P1p3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              P1p3_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            P1p3_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            P1p3_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              P1p3_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(P1p3_DW.HILInitialize_Card,
          &P1p3_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &P1p3_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P1p3_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(P1p3_DW.HILInitialize_Card,
          &P1p3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &P1p3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P1p3_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &P1p3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = P1p3_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &P1p3_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = P1p3_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &P1p3_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = P1p3_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &P1p3_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &P1p3_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &P1p3_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &P1p3_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = P1p3_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &P1p3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P1p3_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_pwm_channels, 8U,
        &P1p3_DW.HILInitialize_POSortedFreqs[0],
        &P1p3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }

    if ((P1p3_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (P1p3_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &P1p3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P1p3_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_pwm_channels, 8U, &P1p3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }

    if (P1p3_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &P1p3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P1p3_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state(P1p3_DW.HILInitialize_Card,
        P1p3_P.HILInitialize_pwm_channels, 8U, &P1p3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

  /* S-Function Block: P1p3/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(P1p3_DW.HILInitialize_Card,
      P1p3_P.HILReadEncoderTimebase_samples_,
      P1p3_P.HILReadEncoderTimebase_channels, 3,
      &P1p3_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P1p3_M, _rt_error_message);
    }
  }

  /* Start for RateTransition: '<S3>/Rate Transition: y' */
  P1p3_B.RateTransitiony = P1p3_P.RateTransitiony_X0;

  /* Start for RateTransition: '<S3>/Rate Transition: x' */
  P1p3_B.RateTransitionx = P1p3_P.RateTransitionx_X0;

  /* Start for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: P1p3/Joystick/Game Controller (game_controller_block) */
  {
    if (P1p3_P.GameController_Enabled) {
      t_double deadzone[6];
      t_double saturation[6];
      t_int index;
      t_error result;
      for (index = 0; index < 6; index++) {
        deadzone[index] = -1;
      }

      for (index = 0; index < 6; index++) {
        saturation[index] = -1;
      }

      result = game_controller_open(P1p3_P.GameController_ControllerNumber,
        P1p3_P.GameController_BufferSize, deadzone, saturation,
        P1p3_P.GameController_AutoCenter, 0, 1.0,
        &P1p3_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p3_M, _rt_error_message);
      }
    }
  }

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition: y' */
  P1p3_DW.RateTransitiony_Buffer0 = P1p3_P.RateTransitiony_X0;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition: x' */
  P1p3_DW.RateTransitionx_Buffer0 = P1p3_P.RateTransitionx_X0;

  /* InitializeConditions for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  P1p3_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  P1p3_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  P1p3_X.TravelTransferFcn_CSTATE = 0.0;
}

/* Model terminate function */
void P1p3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: P1p3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(P1p3_DW.HILInitialize_Card);
    hil_monitor_stop_all(P1p3_DW.HILInitialize_Card);
    is_switching = false;
    if ((P1p3_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (P1p3_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P1p3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P1p3_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((P1p3_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (P1p3_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &P1p3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P1p3_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(P1p3_DW.HILInitialize_Card
                         , P1p3_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , P1p3_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &P1p3_DW.HILInitialize_AOVoltages[0]
                         , &P1p3_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(P1p3_DW.HILInitialize_Card,
            P1p3_P.HILInitialize_analog_output_cha, num_final_analog_outputs,
            &P1p3_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(P1p3_DW.HILInitialize_Card,
            P1p3_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &P1p3_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P1p3_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(P1p3_DW.HILInitialize_Card);
    hil_monitor_delete_all(P1p3_DW.HILInitialize_Card);
    hil_close(P1p3_DW.HILInitialize_Card);
    P1p3_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: P1p3/Joystick/Game Controller (game_controller_block) */
  {
    if (P1p3_P.GameController_Enabled) {
      game_controller_close(P1p3_DW.GameController_Controller);
      P1p3_DW.GameController_Controller = NULL;
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  P1p3_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  P1p3_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  P1p3_initialize();
}

void MdlTerminate(void)
{
  P1p3_terminate();
}

/* Registration function */
RT_MODEL_P1p3_T *P1p3(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)P1p3_M, 0,
                sizeof(RT_MODEL_P1p3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&P1p3_M->solverInfo, &P1p3_M->Timing.simTimeStep);
    rtsiSetTPtr(&P1p3_M->solverInfo, &rtmGetTPtr(P1p3_M));
    rtsiSetStepSizePtr(&P1p3_M->solverInfo, &P1p3_M->Timing.stepSize0);
    rtsiSetdXPtr(&P1p3_M->solverInfo, &P1p3_M->ModelData.derivs);
    rtsiSetContStatesPtr(&P1p3_M->solverInfo, (real_T **)
                         &P1p3_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&P1p3_M->solverInfo, &P1p3_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&P1p3_M->solverInfo, (&rtmGetErrorStatus(P1p3_M)));
    rtsiSetRTModelPtr(&P1p3_M->solverInfo, P1p3_M);
  }

  rtsiSetSimTimeStep(&P1p3_M->solverInfo, MAJOR_TIME_STEP);
  P1p3_M->ModelData.intgData.f[0] = P1p3_M->ModelData.odeF[0];
  P1p3_M->ModelData.contStates = ((real_T *) &P1p3_X);
  rtsiSetSolverData(&P1p3_M->solverInfo, (void *)&P1p3_M->ModelData.intgData);
  rtsiSetSolverName(&P1p3_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = P1p3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    P1p3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    P1p3_M->Timing.sampleTimes = (&P1p3_M->Timing.sampleTimesArray[0]);
    P1p3_M->Timing.offsetTimes = (&P1p3_M->Timing.offsetTimesArray[0]);

    /* task periods */
    P1p3_M->Timing.sampleTimes[0] = (0.0);
    P1p3_M->Timing.sampleTimes[1] = (0.002);
    P1p3_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    P1p3_M->Timing.offsetTimes[0] = (0.0);
    P1p3_M->Timing.offsetTimes[1] = (0.0);
    P1p3_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(P1p3_M, &P1p3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = P1p3_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = P1p3_M->Timing.perTaskSampleHitsArray;
    P1p3_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    P1p3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(P1p3_M, -1);
  P1p3_M->Timing.stepSize0 = 0.002;
  P1p3_M->Timing.stepSize1 = 0.002;
  P1p3_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  P1p3_M->Sizes.checksums[0] = (1489397254U);
  P1p3_M->Sizes.checksums[1] = (3917585660U);
  P1p3_M->Sizes.checksums[2] = (4194282055U);
  P1p3_M->Sizes.checksums[3] = (2265453667U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    P1p3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(P1p3_M->extModeInfo,
      &P1p3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(P1p3_M->extModeInfo, P1p3_M->Sizes.checksums);
    rteiSetTPtr(P1p3_M->extModeInfo, rtmGetTPtr(P1p3_M));
  }

  P1p3_M->solverInfoPtr = (&P1p3_M->solverInfo);
  P1p3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&P1p3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&P1p3_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  P1p3_M->ModelData.blockIO = ((void *) &P1p3_B);

  {
    P1p3_B.RateTransitiony = 0.0;
    P1p3_B.Joystick_gain_y = 0.0;
    P1p3_B.ElevationCounttorad = 0.0;
    P1p3_B.Gain = 0.0;
    P1p3_B.Sum1 = 0.0;
    P1p3_B.RateTransitionx = 0.0;
    P1p3_B.Joystick_gain_x = 0.0;
    P1p3_B.Gain_d = 0.0;
    P1p3_B.PitchCounttorad = 0.0;
    P1p3_B.Gain_i = 0.0;
    P1p3_B.Gain_b = 0.0;
    P1p3_B.TravelCounttorad = 0.0;
    P1p3_B.Gain_dc = 0.0;
    P1p3_B.Gain_p = 0.0;
    P1p3_B.GameController_o4 = 0.0;
    P1p3_B.GameController_o5 = 0.0;
  }

  /* parameters */
  P1p3_M->ModelData.defaultParam = ((real_T *)&P1p3_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &P1p3_X;
    P1p3_M->ModelData.contStates = (x);
    (void) memset((void *)&P1p3_X, 0,
                  sizeof(X_P1p3_T));
  }

  /* states (dwork) */
  P1p3_M->ModelData.dwork = ((void *) &P1p3_DW);
  (void) memset((void *)&P1p3_DW, 0,
                sizeof(DW_P1p3_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p3_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p3_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p3_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p3_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p3_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p3_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p3_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p3_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  P1p3_DW.RateTransitiony_Buffer0 = 0.0;
  P1p3_DW.RateTransitionx_Buffer0 = 0.0;
  P1p3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  P1p3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    P1p3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  P1p3_M->Sizes.numContStates = (3);   /* Number of continuous states */
  P1p3_M->Sizes.numY = (0);            /* Number of model outputs */
  P1p3_M->Sizes.numU = (0);            /* Number of model inputs */
  P1p3_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  P1p3_M->Sizes.numSampTimes = (3);    /* Number of sample times */
  P1p3_M->Sizes.numBlocks = (44);      /* Number of blocks */
  P1p3_M->Sizes.numBlockIO = (16);     /* Number of block outputs */
  P1p3_M->Sizes.numBlockPrms = (143);  /* Sum of parameter "widths" */
  return P1p3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
