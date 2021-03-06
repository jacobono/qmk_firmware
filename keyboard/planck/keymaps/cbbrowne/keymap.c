#include "planck.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

/* Each layer is given a name to aid in readability, which is then
   used in the keymap matrix below.  The underscores do not denote 
   anything - you can have a layer called STUFF or any other name.

   Layer names don't all need to be of the same length, obviously, and
   you could also skip them entirely and just use numbers, though that
   means needing to manage the numbers.

   It is preferable to keep the symbols short so that a line worth of
   key mappings fits compactly onto a line of code. */

/* This was originally based on planck/keymaps/default/default.c, and
   then cbbrowne has revised things */

/* Things I did not like about the default mapping 

   - I find control too hard to get to.  I think I'll want it on a
     left finger.  Gonna need to lose something to do that...
   - Almost certainly, KC_LCTL should be on [2][1]
   - having dash on [lower-j] is a bit nonintuitive, but may be OK
   - I'll bet I should switch ESC/TAB
   - I'm suspicious that I want to shift M(0) from [4][1] to [4][2],
     and shift ESC off the first column so KC_LCTL and KC_LALT can
     be on the first column.
   - I think I wanna swap ' and ENTER

   - All of the above are done :-)

   - I'm keeping Colemak and Dvorak around for reference, and added
     Workman just for fun.  They're useless to me, though.
*/


/* Some interesting things implemented

   - There is a macro that writes out "cbbrowne" just because I could
   - There is a (somewhat cruddy) linear congruential random number
     generator.
     - I would like to be seeding it with clock info to make it look
       more random
   - There are two macros that use the random number generators
     - one, M_RANDDIGIT, generates a random digit based on state
       of the random number generator
     - the other, M_RANDLETTER, generates a random letter based on state
       of the random number generator
     - in both, note the use of register_code()/unregister_code()
       to indicate the desired key
*/

/* Other things to do...

   - Need to think about what zsh and readline actions I use lots
   - Wanna figure out macros, so I can put in a "cbbrowne" macro
   - Ought to ensure that Control-Alt-Delete is convenient enough
   - How about Alt-F1 thru Alt-F8?
   - What's the keystroke to get from X to console these days?
   - I do indeed want a sweet number pad!
   - A layer for doing console switching would not be a bad idea
*/

enum layers {
  _QW = 0,  /* Qwerty mapping */
  _LW, /* Lower layer, where top line has symbols !@#$%^&*() */
  _RS, /* Raised layer, where top line has digits 1234567890 */
  _KP, /* Key pad */
};

enum macro_id {
  M_LED = 0,
  M_USERNAME,
  M_RANDDIGIT,
  M_RANDLETTER
};

/* Note that Planck has dimensions 4 rows x 12 columns */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT },
  {KC_TAB,  M(M_LED), KC_LALT, KC_LGUI, MO(_LW), KC_SPC,  KC_SPC,  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_RS] = { /* RAISE */
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_KP), DF(_KP), RESET,   KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_LW] = { /* LOWER */
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_KP), DF(_KP), RESET,   KC_TRNS},
  {KC_TRNS, DF(_KP), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_KP] = { /* Key Pad */
  {KC_ESC,  M(M_USERNAME),    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_KP_ENTER, KC_KP_PLUS, KC_KP_PLUS, KC_KP_ENTER, KC_BSPC},
  {KC_LCTL, M(M_RANDDIGIT),    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_KP_MINUS, KC_7, KC_8,    KC_9,  KC_ENT},
  {KC_LSFT, M(M_RANDLETTER),    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_KP_PLUS,    KC_4, KC_5,  KC_6, KC_DOT},
  {BL_STEP, M(M_LED), KC_LALT, KC_LGUI, KC_NO, KC_SPC,  KC_SPC,  DF(_QW),   KC_1, KC_2, KC_3,  KC_0}
}
};

const uint16_t PROGMEM fn_actions[] = {
};

/* This bit of logic seeds a wee linear congruential random number generator */

static uint16_t random_value = 157;
#define randadd 53
#define randmul 181
#define randmod 167

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
  case M_LED:
    if (record->event.pressed) {
      register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
      backlight_step();
#endif
    } else {
      unregister_code(KC_RSFT);
    }
    break;	    
  case M_USERNAME:
    if (record->event.pressed) {
      return MACRO( I(1), T(C), T(B), T(B), T(R), T(O), T(W), T(N), T(E));
    } else {
      return MACRO_NONE ;
    }
    break;
  case M_RANDDIGIT:
    /* Generate, based on random number generator, a keystroke for
       a numeric digit chosen at random */
    random_value = ((random_value + randadd) * randmul) % randmod;
    if (record->event.pressed) 
    switch(random_value % 10) {
    case 0:
      register_code (KC_0);
      unregister_code (KC_0);
      break;
    case 1:
      register_code (KC_1);
      unregister_code (KC_1);
      break;
    case 2:
      register_code (KC_2);
      unregister_code (KC_2);
      break;
    case 3:
      register_code (KC_3);
      unregister_code (KC_3);
      break;
    case 4:
      register_code (KC_4);
      unregister_code (KC_4);
      break;
    case 5:
      register_code (KC_5);
      unregister_code (KC_5);
      break;
    case 6:
      register_code (KC_6);
      unregister_code (KC_6);
      break;
    case 7:
      register_code (KC_7);
      unregister_code (KC_7);
      break;
    case 8:
      register_code (KC_8);
      unregister_code (KC_8);
      break;
    case 9:
      register_code (KC_9);
      unregister_code (KC_9);
      break;
    }
    break;
  case M_RANDLETTER:
    /* Generate, based on random number generator, a keystroke for
       a letter chosen at random */
    random_value = ((random_value + randadd) * randmul) % randmod;
    if (record->event.pressed) 
    switch(random_value % 26) {
    case 0:
      register_code(KC_A);
      unregister_code(KC_A);
      break;
    case 1:
      register_code(KC_B);
      unregister_code(KC_B);
      break;
    case 2:
      register_code(KC_C);
      unregister_code(KC_C);
      break;
    case 3:
      register_code(KC_D);
      unregister_code(KC_D);
      break;
    case 4:
      register_code(KC_E);
      unregister_code(KC_E);
      break;
    case 5:
      register_code(KC_F);
      unregister_code(KC_F);
      break;
    case 6:
      register_code(KC_G);
      unregister_code(KC_G);
      break;
    case 7:
      register_code(KC_H);
      unregister_code(KC_H);
      break;
    case 8:
      register_code(KC_I);
      unregister_code(KC_I);
      break;
    case 9:
      register_code(KC_J);
      unregister_code(KC_J);
      break;
    case 10:
      register_code(KC_K);
      unregister_code(KC_K);
      break;
    case 11:
      register_code(KC_L);
      unregister_code(KC_L);
      break;
    case 12:
      register_code(KC_M); 
      unregister_code(KC_M); 
      break;
    case 13:
      register_code(KC_N);
      unregister_code(KC_N);
      break;
    case 14:
      register_code(KC_O);
      unregister_code(KC_O);
      break;
    case 15:
      register_code(KC_P);
      unregister_code(KC_P);
      break;
    case 16:
      register_code(KC_Q);
      unregister_code(KC_Q);
      break;
    case 17:
      register_code(KC_R);
      unregister_code(KC_R);
      break;
    case 18:
      register_code(KC_S);
      unregister_code(KC_S);
      break;
    case 19:
      register_code(KC_T);
      unregister_code(KC_T);
      break;
    case 20:
      register_code(KC_U);
      unregister_code(KC_U);
      break;
    case 21:
      register_code(KC_V);
      unregister_code(KC_V);
      break;
    case 22:
      register_code(KC_W);
      unregister_code(KC_W);
      break;
    case 23:
      register_code(KC_X);
      unregister_code(KC_X);
      break;
    case 24:
      register_code(KC_Y);
      unregister_code(KC_Y);
      break;
    case 25:
      register_code(KC_Z);
      unregister_code(KC_Z);
      break;
    }
    break;
  }
  return MACRO_NONE;
};
