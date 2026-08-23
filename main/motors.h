#pragma once

/*-----------------------------------------------------------------------
 * Configuración de pines para motores (XY-160D)
 *-----------------------------------------------------------------------
 */
#define ENC1_A 2 /* PD2/INT0 */
#define ENC1_B 4 /* PD4 */

#define ENC2_A 3 /* PD3/INT1 */
#define ENC2_B 5 /* PD5 */

#define MOT1_PWM 9  /* PB1 */
#define MOT1_A   14 /* PC0/A0 */
#define MOT1_B   15 /* PC1/A1 */

#define MOT2_PWM 10 /* PB2 */
#define MOT2_A   16 /* PC2/A2 */
#define MOT2_B   17 /* PC3/A3 */

/*-----------------------------------------------------------------------
 * Configuración del motor (TT amarillo 6V)
 *-----------------------------------------------------------------------
 */
#define DEADZONE 40  /* Zona muerta del motor */
#define MIN_PWM  70  /* Mínimo PWM para que gire */
#define MAX_PWM  255 /* PWM máximo (100%) */

#define RAMP_STEP     1 /* Pasos de aceleración del motor */
#define RAMP_DELAY_MS 2 /* Uso en sleepms() de XINU para la tarea mot1 */

/*-----------------------------------------------------------------------
 * Direcciones del motor
 *-----------------------------------------------------------------------
 */
#define DIR_STOP         0
#define DIR_FORWARD      1
#define DIR_REVERSE      2
#define DIR_ROTATE_LEFT  3
#define DIR_ROTATE_RIGHT 4


