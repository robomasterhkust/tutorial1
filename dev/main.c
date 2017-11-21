/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#include "main.h"

RC_Ctl_t* rc;
/*
static BaseSequentialStream* chp = (BaseSequentialStream*)&SDU1;
static const IMUConfigStruct imu1_conf =
  {&SPID5, MPU6500_ACCEL_SCALE_8G, MPU6500_GYRO_SCALE_1000, MPU6500_AXIS_REV_NO};

PIMUStruct pIMU;

#define MPU6500_UPDATE_PERIOD_US 1000000U/MPU6500_UPDATE_FREQ
static THD_WORKING_AREA(Attitude_thread_wa, 4096);
static THD_FUNCTION(Attitude_thread, p)
{
  chRegSetThreadName("IMU Attitude Estimator");

  (void)p;

  imuInit(pIMU, &imu1_conf);

  uint32_t tick = chVTGetSystemTimeX();
  while(true)
  {
    tick += US2ST(MPU6500_UPDATE_PERIOD_US);
    if(chVTGetSystemTimeX() < tick)
      chThdSleepUntil(tick);
    else
    {
      tick = chVTGetSystemTimeX();
      pIMU->errorCode |= IMU_LOSE_FRAME;
    }

    imuGetData(pIMU);
    if(pIMU->inited == 2)
      attitude_update(pIMU);
    else
    {
      attitude_imu_init(pIMU);
      pIMU->inited = 2;
    }

    if(pIMU->accelerometer_not_calibrated || pIMU->gyroscope_not_calibrated)
    {
      chSysLock();
      chThdSuspendS(&(pIMU->imu_Thd));
      chSysUnlock();
    }
  }
}
*/

static THD_WORKING_AREA(Example_wa, 128);
static THD_FUNCTION(Example, p)
{
  chRegSetThreadName("Example");

  (void)p;


  while(!chThdShouldTerminateX())
  {
    chThdSleepMilliseconds(100);
  }

  chThdExit(MSG_OK);
}


/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();


  palSetPad(GPIOE, GPIOE_LED_R);
  palSetPad(GPIOF, GPIOF_LED_G);

  shellStart();
  RC_init();
  rc = RC_get();

  //tft_init(TFT_HORIZONTAL, CYAN, YELLOW, BLACK);

  chThdCreateStatic(Example_wa, sizeof(Example_wa),
                    NORMALPRIO,
                    Example, NULL);
/*
  pIMU = imu_get();
  chThdCreateStatic(Attitude_thread_wa, sizeof(Attitude_thread_wa),
  NORMALPRIO + 5,
                    Attitude_thread, NULL);
                    */

  while (true)
  {
    chThdSleepSeconds(1);
  }

  return 0;
}
