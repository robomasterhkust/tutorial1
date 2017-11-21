/**
 * Edward ZHANG
 * @file    shellcfg.c
 * @brief   definitions of shell command functions
 */
#include "main.h"
#include "shell.h"
#include <string.h>

#define SERIAL_CMD       &SDU1
#define SERIAL_DATA      &SDU1

static thread_t* matlab_thread_handler = NULL;

/*===========================================================================*/
/* Definitions of shell command functions                                    */
/*===========================================================================*/
static THD_WORKING_AREA(Shell_thread_wa, 1024);
void cmd_attitude(BaseSequentialStream * chp, int argc, char *argv[])
{
  /*
  (void) argc,argv;
  PIMUStruct imu = imu_get();

  chprintf(chp,"Roll: %4f\r\n", imu->euler_angle[Roll]*180.0f/M_PI);
  chprintf(chp,"Pitch:%4f\r\n", imu->euler_angle[Pitch]*180.0f/M_PI);
  chprintf(chp,"Yaw:  %4f\r\n", imu->euler_angle[Yaw]*180.0f/M_PI);
  */
}

void cmd_rc(BaseSequentialStream * chp, int argc, char *argv[])
{
  (void) argc,argv;
  RC_Ctl_t* rc = RC_get();

  chprintf(chp,"channel0:  %4d\r\n", rc->rc.channel0);
  chprintf(chp,"channel1:  %4d\r\n", rc->rc.channel1);
  chprintf(chp,"channel2:  %4d\r\n", rc->rc.channel2);
  chprintf(chp,"channel3:  %4d\r\n", rc->rc.channel3);

}

void cmd_led(BaseSequentialStream * chp, int argc, char *argv[])
{
  /* TODO: Turn the red led on and off using this command*/
}


/**
 * @brief array of shell commands, put the corresponding command and functions below
 * {"command", callback_function}
 */
static const ShellCommand commands[] =
{
  {"atti", cmd_attitude},
  {"rc", cmd_rc},
  {"led", cmd_led},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 =
{
  (BaseSequentialStream *)SERIAL_CMD,
  commands
};

/**
 * @brief start the shell service
 * @require enable the corresponding serial ports in mcuconf.h and board.h
 *          Select the SERIAL_CMD port in main.h
 *
 * @api
 */
void shellStart(void)
{
  //sdStart(SERIAL_CMD, NULL);
  /*
   * Initializes a serial-over-USB CDC driver.
   */
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  /*
   * Activates the USB driver and then the USB bus pull-up on D+.
   * Note, a delay is inserted in order to not have to disconnect the cable
   * after a reset.
   */


  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);

  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  shellInit();

  shellCreateStatic(&shell_cfg1, Shell_thread_wa,
      sizeof(Shell_thread_wa), NORMALPRIO);

}
