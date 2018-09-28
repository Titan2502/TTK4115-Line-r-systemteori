/*
 * P1p4.c
 *
 * Code generation for model "P1p4".
 *
 * Model version              : 1.91
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Fri Sep 28 12:35:16 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "P1p4.h"
#include "P1p4_private.h"
#include "P1p4_dt.h"

/* Block signals (auto storage) */
B_P1p4_T P1p4_B;

/* Continuous states */
X_P1p4_T P1p4_X;

/* Block states (auto storage) */
DW_P1p4_T P1p4_DW;

/* Real-time model */
RT_MODEL_P1p4_T P1p4_M_;
RT_MODEL_P1p4_T *const P1p4_M = &P1p4_M_;
static void rate_monotonic_scheduler(void);

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(P1p4_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(P1p4_M, 2);
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
  if (P1p4_M->Timing.TaskCounters.TID[1] == 0) {
    P1p4_M->Timing.RateInteraction.TID1_2 = (P1p4_M->Timing.TaskCounters.TID[2] ==
      0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    P1p4_M->Timing.perTaskSampleHits[5] = P1p4_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (P1p4_M->Timing.TaskCounters.TID[2])++;
  if ((P1p4_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    P1p4_M->Timing.TaskCounters.TID[2] = 0;
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
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  P1p4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void P1p4_output0(void)                /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_TmpSignalConversionAtToFile[6];
  real_T rtb_DeadZoney;
  real_T rtb_Backgain;
  real_T rtb_Sum_p;
  real_T rtb_Add;
  if (rtmIsMajorTimeStep(P1p4_M)) {
    /* set solver stop time */
    if (!(P1p4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&P1p4_M->solverInfo, ((P1p4_M->Timing.clockTickH0 +
        1) * P1p4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&P1p4_M->solverInfo, ((P1p4_M->Timing.clockTick0 + 1)
        * P1p4_M->Timing.stepSize0 + P1p4_M->Timing.clockTickH0 *
        P1p4_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(P1p4_M)) {
    P1p4_M->Timing.t[0] = rtsiGetT(&P1p4_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(P1p4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

    /* S-Function Block: P1p4/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(P1p4_DW.HILReadEncoderTimebase_Task, 1,
        &P1p4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 = P1p4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 = P1p4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_DeadZoney = P1p4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S3>/Elevation: Count to rad' */
    P1p4_B.ElevationCounttorad = P1p4_P.ElevationCounttorad_Gain * rtb_DeadZoney;

    /* Gain: '<S7>/Gain' */
    P1p4_B.Gain = P1p4_P.Gain_Gain * P1p4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/offset_e'
     */
    P1p4_B.Sum1 = P1p4_B.Gain + P1p4_P.offset_e_Value;
  }

  /* Integrator: '<S6>/Integrator'
   *
   * Regarding '<S6>/Integrator':
   *  Limited Integrator
   */
  if (P1p4_X.Integrator_CSTATE >= P1p4_P.Integrator_UpperSat ) {
    P1p4_X.Integrator_CSTATE = P1p4_P.Integrator_UpperSat;
  } else if (P1p4_X.Integrator_CSTATE <= (P1p4_P.Integrator_LowerSat) ) {
    P1p4_X.Integrator_CSTATE = (P1p4_P.Integrator_LowerSat);
  }

  rtb_Backgain = P1p4_X.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(P1p4_M)) {
    /* Gain: '<S3>/Travel: Count to rad' */
    P1p4_B.TravelCounttorad = P1p4_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S11>/Gain' */
    P1p4_B.Gain_p = P1p4_P.Gain_Gain_a * P1p4_B.TravelCounttorad;
  }

  /* Gain: '<S12>/Gain' incorporates:
   *  TransferFcn: '<S3>/Travel: Transfer Fcn'
   */
  P1p4_B.Gain_d = (P1p4_P.TravelTransferFcn_C * P1p4_X.TravelTransferFcn_CSTATE
                   + P1p4_P.TravelTransferFcn_D * P1p4_B.TravelCounttorad) *
    P1p4_P.Gain_Gain_l;
  if (rtmIsMajorTimeStep(P1p4_M)) {
    /* Gain: '<S3>/Pitch: Count to rad' */
    P1p4_B.PitchCounttorad = P1p4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    P1p4_B.Gain_i = P1p4_P.Gain_Gain_ar * P1p4_B.PitchCounttorad;
  }

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S3>/Pitch: Transfer Fcn'
   */
  P1p4_B.Gain_b = (P1p4_P.PitchTransferFcn_C * P1p4_X.PitchTransferFcn_CSTATE +
                   P1p4_P.PitchTransferFcn_D * P1p4_B.PitchCounttorad) *
    P1p4_P.Gain_Gain_ae;

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S3>/Elevation: Transfer Fcn'
   */
  P1p4_B.Gain_dg = (P1p4_P.ElevationTransferFcn_C *
                    P1p4_X.ElevationTransferFcn_CSTATE +
                    P1p4_P.ElevationTransferFcn_D * P1p4_B.ElevationCounttorad) *
    P1p4_P.Gain_Gain_n;
  if (rtmIsMajorTimeStep(P1p4_M)) {
    /* Constant: '<Root>/e_ref' */
    P1p4_B.e_ref = P1p4_P.e_ref_Value;
  }

  /* Sum: '<S2>/Sum' incorporates:
   *  Gain: '<Root>/Deg_2_rad'
   */
  rtb_Sum_p = P1p4_B.e_ref - P1p4_P.Deg_2_rad_Gain * P1p4_B.Sum1;

  /* Sum: '<S6>/Sum' incorporates:
   *  Gain: '<Root>/Deg_2_rad'
   *  Gain: '<S6>/K_ed'
   *  Gain: '<S6>/K_ep'
   */
  P1p4_B.Sum = (P1p4_P.K_ep_Gain * rtb_Sum_p + rtb_Backgain) -
    P1p4_P.Deg_2_rad_Gain * P1p4_B.Gain_dg * P1p4_P.K_ed_Gain;
  if (rtmIsMajorTimeStep(P1p4_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo FileInport1' */
    rtb_TmpSignalConversionAtToFile[0] = P1p4_B.Gain_p;
    rtb_TmpSignalConversionAtToFile[1] = P1p4_B.Gain_d;
    rtb_TmpSignalConversionAtToFile[2] = P1p4_B.Gain_i;
    rtb_TmpSignalConversionAtToFile[3] = P1p4_B.Gain_b;
    rtb_TmpSignalConversionAtToFile[4] = P1p4_B.Sum1;
    rtb_TmpSignalConversionAtToFile[5] = P1p4_B.Gain_dg;

    /* ToFile: '<Root>/To File' */
    if (rtmIsMajorTimeStep(P1p4_M)) {
      {
        if (!(++P1p4_DW.ToFile_IWORK.Decimation % 1) &&
            (P1p4_DW.ToFile_IWORK.Count*7)+1 < 100000000 ) {
          FILE *fp = (FILE *) P1p4_DW.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[7];
            P1p4_DW.ToFile_IWORK.Decimation = 0;
            u[0] = P1p4_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToFile[0];
            u[2] = rtb_TmpSignalConversionAtToFile[1];
            u[3] = rtb_TmpSignalConversionAtToFile[2];
            u[4] = rtb_TmpSignalConversionAtToFile[3];
            u[5] = rtb_TmpSignalConversionAtToFile[4];
            u[6] = rtb_TmpSignalConversionAtToFile[5];
            if (fwrite(u, sizeof(real_T), 7, fp) != 7) {
              rtmSetErrorStatus(P1p4_M, "Error writing to MAT-file P1p4.mat");
              return;
            }

            if (((++P1p4_DW.ToFile_IWORK.Count)*7)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file P1p4.mat.\n");
            }
          }
        }
      }
    }

    /* ToFile: '<Root>/To File1' */
    if (rtmIsMajorTimeStep(P1p4_M)) {
      {
        if (!(++P1p4_DW.ToFile1_IWORK.Decimation % 1) &&
            (P1p4_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
          FILE *fp = (FILE *) P1p4_DW.ToFile1_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[2];
            P1p4_DW.ToFile1_IWORK.Decimation = 0;
            u[0] = P1p4_M->Timing.t[1];
            u[1] = P1p4_B.Sum;
            if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
              rtmSetErrorStatus(P1p4_M, "Error writing to MAT-file P1p4_Vs.mat");
              return;
            }

            if (((++P1p4_DW.ToFile1_IWORK.Count)*2)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file P1p4_Vs.mat.\n");
            }
          }
        }
      }
    }

    /* Constant: '<Root>/e_ref1' */
    P1p4_B.e_ref1 = P1p4_P.e_ref1_Value;
  }

  /* Sum: '<S5>/Sum1' incorporates:
   *  Gain: '<Root>/Deg_2_rad'
   *  Gain: '<S5>/K_pd '
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum'
   */
  rtb_Backgain = (P1p4_B.e_ref1 - P1p4_P.Deg_2_rad_Gain * P1p4_B.Gain_i) *
    P1p4_P.K_pp - P1p4_P.Deg_2_rad_Gain * P1p4_B.Gain_b * P1p4_P.K_pd;

  /* Sum: '<S1>/Add' */
  rtb_Add = rtb_Backgain + P1p4_B.Sum;

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (P1p4_B.Sum - rtb_Backgain) * P1p4_P.Backgain_Gain;

  /* Gain: '<S6>/K_ei' */
  P1p4_B.K_ei = P1p4_P.K_ei_Gain * rtb_Sum_p;
  if (rtmIsMajorTimeStep(P1p4_M)) {
  }

  /* Gain: '<S1>/Front gain' */
  rtb_Sum_p = P1p4_P.Frontgain_Gain * rtb_Add;

  /* Saturate: '<S3>/Front motor: Saturation' */
  if (rtb_Sum_p > P1p4_P.FrontmotorSaturation_UpperSat) {
    P1p4_B.FrontmotorSaturation = P1p4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Sum_p < P1p4_P.FrontmotorSaturation_LowerSat) {
    P1p4_B.FrontmotorSaturation = P1p4_P.FrontmotorSaturation_LowerSat;
  } else {
    P1p4_B.FrontmotorSaturation = rtb_Sum_p;
  }

  /* End of Saturate: '<S3>/Front motor: Saturation' */

  /* Saturate: '<S3>/Back motor: Saturation' */
  if (rtb_Backgain > P1p4_P.BackmotorSaturation_UpperSat) {
    P1p4_B.BackmotorSaturation = P1p4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < P1p4_P.BackmotorSaturation_LowerSat) {
    P1p4_B.BackmotorSaturation = P1p4_P.BackmotorSaturation_LowerSat;
  } else {
    P1p4_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S3>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(P1p4_M)) {
    /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

    /* S-Function Block: P1p4/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      P1p4_DW.HILWriteAnalog_Buffer[0] = P1p4_B.FrontmotorSaturation;
      P1p4_DW.HILWriteAnalog_Buffer[1] = P1p4_B.BackmotorSaturation;
      result = hil_write_analog(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILWriteAnalog_channels, 2, &P1p4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
      }
    }

    /* RateTransition: '<S4>/Rate Transition: x' */
    if (P1p4_M->Timing.RateInteraction.TID1_2) {
      P1p4_B.RateTransitionx = P1p4_DW.RateTransitionx_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: x' */

    /* DeadZone: '<S4>/Dead Zone: x' */
    if (P1p4_B.RateTransitionx > P1p4_P.DeadZonex_End) {
      rtb_DeadZoney = P1p4_B.RateTransitionx - P1p4_P.DeadZonex_End;
    } else if (P1p4_B.RateTransitionx >= P1p4_P.DeadZonex_Start) {
      rtb_DeadZoney = 0.0;
    } else {
      rtb_DeadZoney = P1p4_B.RateTransitionx - P1p4_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: x' */

    /* Gain: '<S4>/Joystick_gain_x' incorporates:
     *  Gain: '<S4>/Gain: x'
     */
    P1p4_B.Joystick_gain_x = P1p4_P.Gainx_Gain * rtb_DeadZoney *
      P1p4_P.Joystick_gain_x;

    /* RateTransition: '<S4>/Rate Transition: y' */
    if (P1p4_M->Timing.RateInteraction.TID1_2) {
      P1p4_B.RateTransitiony = P1p4_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: y' */

    /* DeadZone: '<S4>/Dead Zone: y' */
    if (P1p4_B.RateTransitiony > P1p4_P.DeadZoney_End) {
      rtb_DeadZoney = P1p4_B.RateTransitiony - P1p4_P.DeadZoney_End;
    } else if (P1p4_B.RateTransitiony >= P1p4_P.DeadZoney_Start) {
      rtb_DeadZoney = 0.0;
    } else {
      rtb_DeadZoney = P1p4_B.RateTransitiony - P1p4_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: y' */

    /* Gain: '<S4>/Joystick_gain_y' incorporates:
     *  Gain: '<S4>/Gain: y'
     */
    P1p4_B.Joystick_gain_y = P1p4_P.Gainy_Gain * rtb_DeadZoney *
      P1p4_P.Joystick_gain_y;
  }
}

/* Model update function for TID0 */
void P1p4_update0(void)                /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(P1p4_M)) {
    rt_ertODEUpdateContinuousStates(&P1p4_M->solverInfo);
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
  if (!(++P1p4_M->Timing.clockTick0)) {
    ++P1p4_M->Timing.clockTickH0;
  }

  P1p4_M->Timing.t[0] = rtsiGetSolverStopTime(&P1p4_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P1p4_M->Timing.clockTick1)) {
    ++P1p4_M->Timing.clockTickH1;
  }

  P1p4_M->Timing.t[1] = P1p4_M->Timing.clockTick1 * P1p4_M->Timing.stepSize1 +
    P1p4_M->Timing.clockTickH1 * P1p4_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void P1p4_derivatives(void)
{
  XDot_P1p4_T *_rtXdot;
  _rtXdot = ((XDot_P1p4_T *) P1p4_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S6>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( P1p4_X.Integrator_CSTATE <= (P1p4_P.Integrator_LowerSat) );
    usat = ( P1p4_X.Integrator_CSTATE >= P1p4_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (P1p4_B.K_ei > 0)) ||
        (usat && (P1p4_B.K_ei < 0)) ) {
      ((XDot_P1p4_T *) P1p4_M->ModelData.derivs)->Integrator_CSTATE =
        P1p4_B.K_ei;
    } else {
      /* in saturation */
      ((XDot_P1p4_T *) P1p4_M->ModelData.derivs)->Integrator_CSTATE = 0.0;
    }
  }

  /* Derivatives for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += P1p4_P.TravelTransferFcn_A *
    P1p4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += P1p4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += P1p4_P.PitchTransferFcn_A *
    P1p4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += P1p4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += P1p4_P.ElevationTransferFcn_A *
    P1p4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += P1p4_B.ElevationCounttorad;
}

/* Model output function for TID2 */
void P1p4_output2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: P1p4/Joystick/Game Controller (game_controller_block) */
  {
    if (P1p4_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(P1p4_DW.GameController_Controller, &state,
        &new_data);
      if (result == 0) {
        P1p4_B.GameController_o4 = state.x;
        P1p4_B.GameController_o5 = state.y;
      }
    } else {
      P1p4_B.GameController_o4 = 0;
      P1p4_B.GameController_o5 = 0;
    }
  }
}

/* Model update function for TID2 */
void P1p4_update2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* Update for RateTransition: '<S4>/Rate Transition: x' */
  P1p4_DW.RateTransitionx_Buffer0 = P1p4_B.GameController_o4;

  /* Update for RateTransition: '<S4>/Rate Transition: y' */
  P1p4_DW.RateTransitiony_Buffer0 = P1p4_B.GameController_o5;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P1p4_M->Timing.clockTick2)) {
    ++P1p4_M->Timing.clockTickH2;
  }

  P1p4_M->Timing.t[2] = P1p4_M->Timing.clockTick2 * P1p4_M->Timing.stepSize2 +
    P1p4_M->Timing.clockTickH2 * P1p4_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void P1p4_output(int_T tid)
{
  switch (tid) {
   case 0 :
    P1p4_output0();
    break;

   case 2 :
    P1p4_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void P1p4_update(int_T tid)
{
  switch (tid) {
   case 0 :
    P1p4_update0();
    break;

   case 2 :
    P1p4_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void P1p4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: P1p4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &P1p4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P1p4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(P1p4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P1p4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(P1p4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P1p4_M, _rt_error_message);
      return;
    }

    if ((P1p4_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (P1p4_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &P1p4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = P1p4_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &P1p4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = P1p4_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_analog_input_chan, 8U,
        &P1p4_DW.HILInitialize_AIMinimums[0], &P1p4_DW.HILInitialize_AIMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }

    if ((P1p4_P.HILInitialize_set_analog_output && !is_switching) ||
        (P1p4_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &P1p4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = P1p4_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &P1p4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = P1p4_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_analog_output_cha, 8U,
        &P1p4_DW.HILInitialize_AOMinimums[0], &P1p4_DW.HILInitialize_AOMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }

    if ((P1p4_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (P1p4_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P1p4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P1p4_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_analog_output_cha, 8U,
        &P1p4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }

    if (P1p4_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P1p4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P1p4_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (P1p4_DW.HILInitialize_Card, P1p4_P.HILInitialize_analog_output_cha, 8U,
         &P1p4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }

    if ((P1p4_P.HILInitialize_set_encoder_param && !is_switching) ||
        (P1p4_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &P1p4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = P1p4_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_encoder_channels, 8U, (t_encoder_quadrature_mode *)
        &P1p4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }

    if ((P1p4_P.HILInitialize_set_encoder_count && !is_switching) ||
        (P1p4_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &P1p4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = P1p4_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_encoder_channels, 8U,
        &P1p4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }

    if ((P1p4_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (P1p4_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &P1p4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = P1p4_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &P1p4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          P1p4_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &P1p4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            P1p4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            P1p4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              P1p4_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            P1p4_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            P1p4_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              P1p4_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(P1p4_DW.HILInitialize_Card,
          &P1p4_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &P1p4_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P1p4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(P1p4_DW.HILInitialize_Card,
          &P1p4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &P1p4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P1p4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &P1p4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = P1p4_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &P1p4_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = P1p4_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &P1p4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = P1p4_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &P1p4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &P1p4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &P1p4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &P1p4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = P1p4_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &P1p4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P1p4_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_pwm_channels, 8U,
        &P1p4_DW.HILInitialize_POSortedFreqs[0],
        &P1p4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }

    if ((P1p4_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (P1p4_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &P1p4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P1p4_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_pwm_channels, 8U, &P1p4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }

    if (P1p4_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &P1p4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P1p4_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state(P1p4_DW.HILInitialize_Card,
        P1p4_P.HILInitialize_pwm_channels, 8U, &P1p4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: P1p4/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(P1p4_DW.HILInitialize_Card,
      P1p4_P.HILReadEncoderTimebase_samples_,
      P1p4_P.HILReadEncoderTimebase_channels, 3,
      &P1p4_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P1p4_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    char fileName[509] = "P1p4.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(P1p4_M, "Error creating .mat file P1p4.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,7,0,"ans")) {
      rtmSetErrorStatus(P1p4_M, "Error writing mat file header to file P1p4.mat");
      return;
    }

    P1p4_DW.ToFile_IWORK.Count = 0;
    P1p4_DW.ToFile_IWORK.Decimation = -1;
    P1p4_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "P1p4_Vs.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(P1p4_M, "Error creating .mat file P1p4_Vs.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(P1p4_M,
                        "Error writing mat file header to file P1p4_Vs.mat");
      return;
    }

    P1p4_DW.ToFile1_IWORK.Count = 0;
    P1p4_DW.ToFile1_IWORK.Decimation = -1;
    P1p4_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S4>/Rate Transition: x' */
  P1p4_B.RateTransitionx = P1p4_P.RateTransitionx_X0;

  /* Start for RateTransition: '<S4>/Rate Transition: y' */
  P1p4_B.RateTransitiony = P1p4_P.RateTransitiony_X0;

  /* Start for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: P1p4/Joystick/Game Controller (game_controller_block) */
  {
    if (P1p4_P.GameController_Enabled) {
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

      result = game_controller_open(P1p4_P.GameController_ControllerNumber,
        P1p4_P.GameController_BufferSize, deadzone, saturation,
        P1p4_P.GameController_AutoCenter, 0, 1.0,
        &P1p4_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P1p4_M, _rt_error_message);
      }
    }
  }

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  P1p4_X.Integrator_CSTATE = P1p4_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  P1p4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  P1p4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  P1p4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for RateTransition: '<S4>/Rate Transition: x' */
  P1p4_DW.RateTransitionx_Buffer0 = P1p4_P.RateTransitionx_X0;

  /* InitializeConditions for RateTransition: '<S4>/Rate Transition: y' */
  P1p4_DW.RateTransitiony_Buffer0 = P1p4_P.RateTransitiony_X0;
}

/* Model terminate function */
void P1p4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: P1p4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(P1p4_DW.HILInitialize_Card);
    hil_monitor_stop_all(P1p4_DW.HILInitialize_Card);
    is_switching = false;
    if ((P1p4_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (P1p4_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P1p4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P1p4_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((P1p4_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (P1p4_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &P1p4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P1p4_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(P1p4_DW.HILInitialize_Card
                         , P1p4_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , P1p4_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &P1p4_DW.HILInitialize_AOVoltages[0]
                         , &P1p4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(P1p4_DW.HILInitialize_Card,
            P1p4_P.HILInitialize_analog_output_cha, num_final_analog_outputs,
            &P1p4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(P1p4_DW.HILInitialize_Card,
            P1p4_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &P1p4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P1p4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(P1p4_DW.HILInitialize_Card);
    hil_monitor_delete_all(P1p4_DW.HILInitialize_Card);
    hil_close(P1p4_DW.HILInitialize_Card);
    P1p4_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) P1p4_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "P1p4.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P1p4_M, "Error closing MAT-file P1p4.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(P1p4_M, "Error reopening MAT-file P1p4.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 7, P1p4_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(P1p4_M,
                          "Error writing header for ans to MAT-file P1p4.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P1p4_M, "Error closing MAT-file P1p4.mat");
        return;
      }

      P1p4_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) P1p4_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "P1p4_Vs.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P1p4_M, "Error closing MAT-file P1p4_Vs.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(P1p4_M, "Error reopening MAT-file P1p4_Vs.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, P1p4_DW.ToFile1_IWORK.Count, "ans")) {
        rtmSetErrorStatus(P1p4_M,
                          "Error writing header for ans to MAT-file P1p4_Vs.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P1p4_M, "Error closing MAT-file P1p4_Vs.mat");
        return;
      }

      P1p4_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: P1p4/Joystick/Game Controller (game_controller_block) */
  {
    if (P1p4_P.GameController_Enabled) {
      game_controller_close(P1p4_DW.GameController_Controller);
      P1p4_DW.GameController_Controller = NULL;
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
  P1p4_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  P1p4_update(tid);
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
  P1p4_initialize();
}

void MdlTerminate(void)
{
  P1p4_terminate();
}

/* Registration function */
RT_MODEL_P1p4_T *P1p4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  P1p4_P.Integrator_UpperSat = rtInf;
  P1p4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)P1p4_M, 0,
                sizeof(RT_MODEL_P1p4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&P1p4_M->solverInfo, &P1p4_M->Timing.simTimeStep);
    rtsiSetTPtr(&P1p4_M->solverInfo, &rtmGetTPtr(P1p4_M));
    rtsiSetStepSizePtr(&P1p4_M->solverInfo, &P1p4_M->Timing.stepSize0);
    rtsiSetdXPtr(&P1p4_M->solverInfo, &P1p4_M->ModelData.derivs);
    rtsiSetContStatesPtr(&P1p4_M->solverInfo, (real_T **)
                         &P1p4_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&P1p4_M->solverInfo, &P1p4_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&P1p4_M->solverInfo, (&rtmGetErrorStatus(P1p4_M)));
    rtsiSetRTModelPtr(&P1p4_M->solverInfo, P1p4_M);
  }

  rtsiSetSimTimeStep(&P1p4_M->solverInfo, MAJOR_TIME_STEP);
  P1p4_M->ModelData.intgData.f[0] = P1p4_M->ModelData.odeF[0];
  P1p4_M->ModelData.contStates = ((real_T *) &P1p4_X);
  rtsiSetSolverData(&P1p4_M->solverInfo, (void *)&P1p4_M->ModelData.intgData);
  rtsiSetSolverName(&P1p4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = P1p4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    P1p4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    P1p4_M->Timing.sampleTimes = (&P1p4_M->Timing.sampleTimesArray[0]);
    P1p4_M->Timing.offsetTimes = (&P1p4_M->Timing.offsetTimesArray[0]);

    /* task periods */
    P1p4_M->Timing.sampleTimes[0] = (0.0);
    P1p4_M->Timing.sampleTimes[1] = (0.002);
    P1p4_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    P1p4_M->Timing.offsetTimes[0] = (0.0);
    P1p4_M->Timing.offsetTimes[1] = (0.0);
    P1p4_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(P1p4_M, &P1p4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = P1p4_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = P1p4_M->Timing.perTaskSampleHitsArray;
    P1p4_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    P1p4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(P1p4_M, -1);
  P1p4_M->Timing.stepSize0 = 0.002;
  P1p4_M->Timing.stepSize1 = 0.002;
  P1p4_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  P1p4_M->Sizes.checksums[0] = (706480510U);
  P1p4_M->Sizes.checksums[1] = (309338589U);
  P1p4_M->Sizes.checksums[2] = (1261261098U);
  P1p4_M->Sizes.checksums[3] = (2145180630U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    P1p4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(P1p4_M->extModeInfo,
      &P1p4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(P1p4_M->extModeInfo, P1p4_M->Sizes.checksums);
    rteiSetTPtr(P1p4_M->extModeInfo, rtmGetTPtr(P1p4_M));
  }

  P1p4_M->solverInfoPtr = (&P1p4_M->solverInfo);
  P1p4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&P1p4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&P1p4_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  P1p4_M->ModelData.blockIO = ((void *) &P1p4_B);

  {
    P1p4_B.ElevationCounttorad = 0.0;
    P1p4_B.Gain = 0.0;
    P1p4_B.Sum1 = 0.0;
    P1p4_B.TravelCounttorad = 0.0;
    P1p4_B.Gain_p = 0.0;
    P1p4_B.Gain_d = 0.0;
    P1p4_B.PitchCounttorad = 0.0;
    P1p4_B.Gain_i = 0.0;
    P1p4_B.Gain_b = 0.0;
    P1p4_B.Gain_dg = 0.0;
    P1p4_B.e_ref = 0.0;
    P1p4_B.Sum = 0.0;
    P1p4_B.e_ref1 = 0.0;
    P1p4_B.K_ei = 0.0;
    P1p4_B.FrontmotorSaturation = 0.0;
    P1p4_B.BackmotorSaturation = 0.0;
    P1p4_B.RateTransitionx = 0.0;
    P1p4_B.Joystick_gain_x = 0.0;
    P1p4_B.RateTransitiony = 0.0;
    P1p4_B.Joystick_gain_y = 0.0;
    P1p4_B.GameController_o4 = 0.0;
    P1p4_B.GameController_o5 = 0.0;
  }

  /* parameters */
  P1p4_M->ModelData.defaultParam = ((real_T *)&P1p4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &P1p4_X;
    P1p4_M->ModelData.contStates = (x);
    (void) memset((void *)&P1p4_X, 0,
                  sizeof(X_P1p4_T));
  }

  /* states (dwork) */
  P1p4_M->ModelData.dwork = ((void *) &P1p4_DW);
  (void) memset((void *)&P1p4_DW, 0,
                sizeof(DW_P1p4_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P1p4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  P1p4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  P1p4_DW.HILWriteAnalog_Buffer[1] = 0.0;
  P1p4_DW.RateTransitionx_Buffer0 = 0.0;
  P1p4_DW.RateTransitiony_Buffer0 = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    P1p4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  P1p4_M->Sizes.numContStates = (4);   /* Number of continuous states */
  P1p4_M->Sizes.numY = (0);            /* Number of model outputs */
  P1p4_M->Sizes.numU = (0);            /* Number of model inputs */
  P1p4_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  P1p4_M->Sizes.numSampTimes = (3);    /* Number of sample times */
  P1p4_M->Sizes.numBlocks = (58);      /* Number of blocks */
  P1p4_M->Sizes.numBlockIO = (22);     /* Number of block outputs */
  P1p4_M->Sizes.numBlockPrms = (153);  /* Sum of parameter "widths" */
  return P1p4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
