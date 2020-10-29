//     /* oAction */
//     #define REX_ACT_WALK 0
//     #define REX_ACT_ATTACKED_MARIO 1
//     #define REX_ACT_JUMP 2
//     #define ATTACK_HANDLER_GPD_ON 9

//     #include "audio_defines.h"

//     #include "literally_everything.h"

//     #include "types.h"
//     extern struct Object *gCurrentObject;
//     #define o gCurrentObject

//     extern struct MarioState *gMarioState;

//     #include <PR/ultratypes.h>

//     #include "literally_everything.h"
//     #include "object_fields.h"

//     #include "interaction.h"
//     #include "object_constants.h"

// #define ATTACK_HANDLER_NOP 0
// #define ATTACK_HANDLER_DIE_IF_HEALTH_NON_POSITIVE 1
// #define ATTACK_HANDLER_KNOCKBACK 2
// #define ATTACK_HANDLER_SQUISHED 3
// #define ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL 4
// #define ATTACK_HANDLER_SET_SPEED_TO_ZERO 5
// #define ATTACK_HANDLER_SPECIAL_WIGGLER_JUMPED_ON 6
// #define ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED 7
// #define ATTACK_HANDLER_SQUISHED_WITH_BLUE_COIN 8

// /* extern void obj_set_hitbox(o, ObjectHitbox);
// extern s32 obj_update_standard_actions(f32);
// extern void cur_obj_update_floor_and_walls();
// extern void cur_obj_init_animation_with_accel_and_sound(s32, f32);
// extern void cur_obj_move_standard(s16);
// extern void obj_resolve_object_collisions(s32 *);
// extern void obj_set_squished_action();
// extern void treat_far_home_as_mario(f32);
// extern void obj_forward_vel_approach(f32, f32);
// extern s32 obj_bounce_off_walls_edges_objects(s32 *);
// extern void cur_obj_play_sound_2(s32);
// extern void cur_obj_rotate_yaw_toward(s16, s16);
// extern s16 random_linear_offset(s16, s16);
// extern void cur_obj_play_sound_at_anim_range(s8, s8, u32);
// extern s32 obj_resolve_collisions_and_turn(s16, s16);
// extern u16 random_u16();
// extern s16 obj_random_fixed_turn(s16); */

// static struct ObjectHitbox sRexHitbox = {
//     /* interactType:      */ INTERACT_BOUNCE_TOP,
//     /* downOffset:        */ 0,
//     /* damageOrCoinValue: */ 1,
//     /* health:            */ 0,
//     /* numLootCoins:      */ 1,
//     /* radius:            */ 90,
//     /* height:            */ 90,
//     /* hurtboxRadius:     */ 70,
//     /* hurtboxHeight:     */ 80,
// };

// static u8 sRexAttackHandlers[][6] = {
//     // regular and tiny
//     {
//         /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
//         /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
//         /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
//         /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_GPD_ON,
//         /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
//         /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
//     },
// };

// void bhv_rex_init(void) {

//     //o->oGoombaScale = 1.0f;
//     //o->oGoombaSize = o->oBehParams2ndByte & GOOMBA_BP_SIZE_MASK;

//     o->oGravity = -8.0f / 3.0f; //* o->oGoombaScale
//     obj_set_hitbox(o, &sRexHitbox);
//     //cur_obj_scale(o->oGoombaScale);
// }

// /**
//  * Enter the jump action and set initial y velocity.
//  */
// static void rex_begin_jump(void) {
//     cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
//     o->oAction = REX_ACT_JUMP;
//     o->oForwardVel = 0.0f;
//     o->oVelY = 50.0f / 3.0f; //* o->oGoombaScale;
// }

// /**
//  * Walk around randomly occasionally jumping. If mario comes within range,
//  * chase him.
//  */
// static void rex_act_walk(void) {
//     treat_far_home_as_mario(1000.0f);

//     obj_forward_vel_approach(o->oGoombaRelativeSpeed, 0.4f);

//     // If walking fast enough, play footstep sounds
//     if (o->oGoombaRelativeSpeed > 4.0f / 3.0f) {
//         cur_obj_play_sound_at_anim_range(2, 17, SOUND_OBJ_GOOMBA_WALK);
//     }

//     if (o->oGoombaTurningAwayFromWall) {
//         o->oGoombaTurningAwayFromWall = obj_resolve_collisions_and_turn(o->oGoombaTargetYaw, 0x200);
//     } else {
//         // If far from home, walk toward home.
//         if (o->oDistanceToMario >= 25000.0f) {
//             o->oGoombaTargetYaw = o->oAngleToMario;
//             o->oGoombaWalkTimer = random_linear_offset(20, 30);
//         }

//         if (!(o->oGoombaTurningAwayFromWall =
//                   obj_bounce_off_walls_edges_objects(&o->oGoombaTargetYaw))) {
//             if (o->oDistanceToMario < 500.0f) {
//                 // If close to mario, begin chasing him. If not already chasing
//                 // him, jump first

//                 if (o->oGoombaRelativeSpeed <= 2.0f) {
//                     rex_begin_jump();
//                 }

//                 o->oGoombaTargetYaw = o->oAngleToMario;
//                 o->oGoombaRelativeSpeed = 20.0f;
//             } else {
//                 // If mario is far away, walk at a normal pace, turning randomly
//                 // and occasionally jumping

//                 o->oGoombaRelativeSpeed = 4.0f / 3.0f;
//                 if (o->oGoombaWalkTimer != 0) {
//                     o->oGoombaWalkTimer -= 1;
//                 } else {
//                     if (random_u16() & 3) {
//                         o->oGoombaTargetYaw = obj_random_fixed_turn(0x2000);
//                         o->oGoombaWalkTimer = random_linear_offset(100, 100);
//                     } else {
//                         rex_begin_jump();
//                         o->oGoombaTargetYaw = obj_random_fixed_turn(0x6000);
//                     }
//                 }
//             }
//         }

//         cur_obj_rotate_yaw_toward(o->oGoombaTargetYaw, 0x200);
//     }
// }

// static void rex_act_attacked_mario(void) {
//         rex_begin_jump();
//         o->oGoombaTargetYaw = o->oAngleToMario;
//         o->oGoombaTurningAwayFromWall = FALSE;
// }

// /**
//  * Move until landing, and rotate toward target yaw.
//  */
// static void rex_act_jump(void) {
//     obj_resolve_object_collisions(NULL);

//     if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
//         o->oAction = REX_ACT_WALK;
//     } else {
//         cur_obj_rotate_yaw_toward(o->oGoombaTargetYaw, 0x800);
//     }
// }

// void bhv_rex_update(void) {
//     // PARTIAL_UPDATE

//     f32 animSpeed;

//     if (obj_update_standard_actions(1.0f)) {

//         cur_obj_update_floor_and_walls();

//         if ((animSpeed = o->oForwardVel * 0.4f) < 1.0f) {
//             animSpeed = 1.0f;
//         }
//         cur_obj_init_animation_with_accel_and_sound(0, animSpeed);

//         switch (o->oAction) {
//             case REX_ACT_WALK:
//                 rex_act_walk();
//                 break;
//             case REX_ACT_ATTACKED_MARIO:
//                 rex_act_attacked_mario();
//                 break;
//             case REX_ACT_JUMP:
//                 rex_act_jump();
//                 break;
//         }

//     if (o->oInteractStatus & INT_STATUS_INTERACTED) {
//         if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO) {
//             if (o->oAction != REX_ACT_ATTACKED_MARIO) {
//                 o->oAction = REX_ACT_ATTACKED_MARIO;
//                 o->oTimer = 0;
//             }
//         } else {
//             s32 attackType = o->oInteractStatus & INT_STATUS_ATTACK_MASK;

//             switch (sRexAttackHandlers[0][attackType - 1]) {
//                 case ATTACK_HANDLER_NOP:
//                     break;

//                 case ATTACK_HANDLER_KNOCKBACK:
//                     //obj_set_knockback_action(attackType);
//                     break;

//                 case ATTACK_HANDLER_SQUISHED:
//                     if (o->header.gfx.scale[1] < 1.0f) {
//                         obj_set_squished_action();
//                     } else {
//                     o->header.gfx.scale[1] = 0.5f;
//                     }
//                     break;
//                 case ATTACK_HANDLER_GPD_ON:
//                     obj_set_squished_action();
//                     break;
//         }
//         }
//         o->oInteractStatus = 0;
//     }

//         cur_obj_move_standard(-78);
//     } else {
//         o->oAnimState = TRUE;
//     }
// }












//     /* oAction */
//     #define GALOOMBA_ACT_WALK 0
//     #define GALOOMBA_ACT_ATTACKED_MARIO 1
//     #define GALOOMBA_ACT_JUMP 2
//     #define GALOOMBA_ACT_FLIPPED 3
//     #define GALOOMBA_ACT_FLIPPED_INIT 4
//     #define ATTACK_HANDLER_GPD_ON 9

//     //#define GRAPH_RENDER_INVISIBLE 0x20

// /* extern s16 object_step(void);
// extern s32 obj_attack_collided_from_other_object(o);
// extern void obj_check_floor_death(s16, s16);
// extern void spawn_mist_particles(void);
// extern void create_sound_spawner(s32);
// extern void cur_obj_init_animation(s32);
// extern void cur_obj_become_tangible(void);
// extern void cur_obj_become_intangible(void);
// extern void cur_obj_get_dropped(void); */

// static struct ObjectHitbox sGaloombaHitbox = {
//     /* interactType:      */ INTERACT_BOUNCE_TOP,
//     /* downOffset:        */ 0,
//     /* damageOrCoinValue: */ 1,
//     /* health:            */ 1,
//     /* numLootCoins:      */ 1,
//     /* radius:            */ 90,
//     /* height:            */ 90,
//     /* hurtboxRadius:     */ 70,
//     /* hurtboxHeight:     */ 80,
// };

// static u8 sGaloombaAttackHandlers[][6] = {
//     // regular and tiny
//     {
//         /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
//         /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
//         /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
//         /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_GPD_ON,
//         /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
//         /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
//     },
// };

// void bhv_galoomba_init(void) {

//     //o->oGoombaScale = 1.0f;
//     //o->oGoombaSize = o->oBehParams2ndByte & GOOMBA_BP_SIZE_MASK;

//     o->oGravity = -8.0f / 3.0f; //* o->oGoombaScale
//     obj_set_hitbox(o, &sGaloombaHitbox);
//     //cur_obj_scale(o->oGoombaScale);
// }

// /**
//  * Enter the jump action and set initial y velocity.
//  */
// static void galoomba_begin_jump(void) {
//     cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
//     o->oAction = GALOOMBA_ACT_JUMP;
//     o->oForwardVel = 0.0f;
//     o->oVelY = 50.0f / 3.0f; //* o->oGoombaScale;
// }

// /**
//  * Walk around randomly occasionally jumping. If mario comes within range,
//  * chase him.
//  */
// static void galoomba_act_walk(void) {
//     treat_far_home_as_mario(1000.0f);

//     obj_forward_vel_approach(o->oGoombaRelativeSpeed, 0.4f);

//     // If walking fast enough, play footstep sounds
//     if (o->oGoombaRelativeSpeed > 4.0f / 3.0f) {
//         cur_obj_play_sound_at_anim_range(2, 17, SOUND_OBJ_GOOMBA_WALK);
//     }

//     if (o->oGoombaTurningAwayFromWall) {
//         o->oGoombaTurningAwayFromWall = obj_resolve_collisions_and_turn(o->oGoombaTargetYaw, 0x200);
//     } else {
//         // If far from home, walk toward home.
//         if (o->oDistanceToMario >= 25000.0f) {
//             o->oGoombaTargetYaw = o->oAngleToMario;
//             o->oGoombaWalkTimer = random_linear_offset(20, 30);
//         }

//         if (!(o->oGoombaTurningAwayFromWall =
//                   obj_bounce_off_walls_edges_objects(&o->oGoombaTargetYaw))) {
//             if (o->oDistanceToMario < 500.0f) {
//                 // If close to mario, begin chasing him. If not already chasing
//                 // him, jump first

//                 if (o->oGoombaRelativeSpeed <= 2.0f) {
//                     galoomba_begin_jump();
//                 }

//                 o->oGoombaTargetYaw = o->oAngleToMario;
//                 o->oGoombaRelativeSpeed = 20.0f;
//             } else {
//                 // If mario is far away, walk at a normal pace, turning randomly
//                 // and occasionally jumping

//                 o->oGoombaRelativeSpeed = 4.0f / 3.0f;
//                 if (o->oGoombaWalkTimer != 0) {
//                     o->oGoombaWalkTimer -= 1;
//                 } else {
//                     if (random_u16() & 3) {
//                         o->oGoombaTargetYaw = obj_random_fixed_turn(0x2000);
//                         o->oGoombaWalkTimer = random_linear_offset(100, 100);
//                     } else {
//                         galoomba_begin_jump();
//                         o->oGoombaTargetYaw = obj_random_fixed_turn(0x6000);
//                     }
//                 }
//             }
//         }

//         cur_obj_rotate_yaw_toward(o->oGoombaTargetYaw, 0x200);
//     }
// }

// static void galoomba_act_attacked_mario(void) {
//         galoomba_begin_jump();
//         o->oGoombaTargetYaw = o->oAngleToMario;
//         o->oGoombaTurningAwayFromWall = FALSE;
// }

// /**
//  * Move until landing, and rotate toward target yaw.
//  */
// static void galoomba_act_jump(void) {
//     obj_resolve_object_collisions(NULL);

//     if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
//         o->oAction = GALOOMBA_ACT_WALK;
//     } else {
//         cur_obj_rotate_yaw_toward(o->oGoombaTargetYaw, 0x800);
//     }
// }

// static void galoomba_act_flipped_init(void) {
//     o->oGravity = 2.5f;
//     o->oFriction = 0.90f;
//     o->oBuoyancy = 1.4f;
//     o->oInteractType = INTERACT_GRABBABLE;
//     //o->oAnimState = 1;
//     //o->activeFlags |= ACTIVE_FLAG_UNK9;
//     o->oAction = GALOOMBA_ACT_FLIPPED;
//     cur_obj_init_animation(2);
// }
// static void galoomba_act_flipped(void) {
//                     //spawn_object(o, MODEL_GALOOMBA, bhvGaloombaBox);
//                     //mark_obj_for_deletion(o);
//                     if(o->header.gfx.unk38.animFrame >= 4) {
//                         cur_obj_init_animation(1);
//                     }
// }

// void galoomba_box_act_move(void) {
//     s16 sp1E = object_step();

//     obj_attack_collided_from_other_object(o);
//     if (sp1E == 1)
//         cur_obj_play_sound_2(SOUND_GENERAL_BOX_LANDING_2);
//     if (sp1E & 1) {
//         if (o->oForwardVel > 20.0f) {
//             cur_obj_play_sound_2(SOUND_ENV_SLIDING);
//         }
//     }

//     if (sp1E & 2) {
//         spawn_mist_particles();
//         obj_spawn_yellow_coins(o, 3);
//         create_sound_spawner(SOUND_OBJ_STOMPED);
//         o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
//     }

//     obj_check_floor_death(sp1E, o->oFloor);
// }

// void bhv_galoomba_update(void) {
//     // PARTIAL_UPDATE

//     f32 animSpeed;

//     if (gMarioState->heldObj != o && o->oGaloombaGrabbed == 1) {
//         cur_obj_become_tangible();
//        o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
//        if (o->oHeldState != HELD_FREE) {
//         cur_obj_get_dropped();
//         o->oForwardVel = 20.0f;
//        }
//        galoomba_box_act_move();
//     }
//     if (gMarioState->heldObj == o) {
//        o->oGaloombaGrabbed = 1;
//        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
//        cur_obj_become_intangible();
//     }

//     if (obj_update_standard_actions(1.0f)) {

//         obj_update_blinking(&o->oGoombaBlinkTimer, 30, 50, 5);
//         cur_obj_update_floor_and_walls();

//         if ((animSpeed = o->oForwardVel * 0.4f) < 1.0f) {
//             animSpeed = 1.0f;
//         }

//         if(o->oAction < GALOOMBA_ACT_FLIPPED)
//             cur_obj_init_animation_with_accel_and_sound(0, animSpeed);

//         switch (o->oAction) {
//             case GALOOMBA_ACT_WALK:
//                 galoomba_act_walk();
//                 break;
//             case GALOOMBA_ACT_ATTACKED_MARIO:
//                 galoomba_act_attacked_mario();
//                 break;
//             case GALOOMBA_ACT_JUMP:
//                 galoomba_act_jump();
//                 break;
//             case GALOOMBA_ACT_FLIPPED_INIT:
//                 galoomba_act_flipped_init();
//                 break;
//             case GALOOMBA_ACT_FLIPPED:
//                 galoomba_act_flipped();
//                 break;
//         }

// if(o->oAction < GALOOMBA_ACT_FLIPPED) {
//     if (o->oInteractStatus & INT_STATUS_INTERACTED) {
//         if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO) {
//             if (o->oAction != GALOOMBA_ACT_ATTACKED_MARIO) {
//                 o->oAction = GALOOMBA_ACT_ATTACKED_MARIO;
//                 o->oTimer = 0;
//             }
//         } else {
//             s32 attackType = o->oInteractStatus & INT_STATUS_ATTACK_MASK;

//             switch (sGaloombaAttackHandlers[0][attackType - 1]) {
//                 case ATTACK_HANDLER_NOP:
//                     break;

//                 case ATTACK_HANDLER_KNOCKBACK:
//                     //obj_set_knockback_action(attackType);
//                     break;

//                 case ATTACK_HANDLER_SQUISHED:
//                     o->oAction = GALOOMBA_ACT_FLIPPED_INIT;
//                     break;
//                 case ATTACK_HANDLER_GPD_ON:
//                     obj_set_squished_action();
//                     break;
//         }
//         }
//         o->oInteractStatus = 0;
//     }
//             cur_obj_move_standard(-78);
// } else {
//     if (o->oInteractStatus & INT_STATUS_INTERACTED) {

//     }
//     o->oInteractStatus = 0;
// }
//     } else {
//         o->oAnimState = TRUE;
//     }
// }

// #define BLOOPER_IDLE 0
// #define BLOOPER_RISE 1
// #define BLOOPER_FALL 2

// #include "engine/surface_collision.h"

// struct Surface *surface;
// f32 ceilHeight;

// static struct ObjectHitbox sBlooperHitbox = {
//     /* interactType:      */ INTERACT_BOUNCE_TOP,
//     /* downOffset:        */ 0,
//     /* damageOrCoinValue: */ 1,
//     /* health:            */ 1,
//     /* numLootCoins:      */ 1,
//     /* radius:            */ 90,
//     /* height:            */ 90,
//     /* hurtboxRadius:     */ 70,
//     /* hurtboxHeight:     */ 80,
// };

// void bhv_blooper_init(void) {
//     obj_set_hitbox(o, &sBlooperHitbox);
// }

// void blooper_act_idle(void) {
//     o->oForwardVel = 0.0f;
//         if (o->oDistanceToMario < 2500.0f) {
//             o->oForwardVel = 7.5f;
//             if(o->oPosY < gMarioState->pos[1] - 100) 
//                 o->oAction = BLOOPER_RISE;
//             if(o->oPosY > gMarioState->pos[1] + 50) 
//                 o->oPosY -= 15.0f;
//         }
// }

// void blooper_act_rise(void) {
//     o->oForwardVel = 15.0f;
//     //cur_obj_compute_vel_xz();
//     //cur_obj_move_using_vel();
//     if(o->header.gfx.scale[0] > 0.75f)
//         o->header.gfx.scale[0] = o->header.gfx.scale[2] = o->header.gfx.scale[0] - 0.05f;
//     else
//         o->header.gfx.scale[0] = o->header.gfx.scale[2] = 0.75f;
//     if(o->oTimer < 30 && o->oPosY < find_water_level(o->oPosX, o->oPosZ) - 300) {
//         o->oPosY = o->oPosY + (30 - o->oTimer);
//         if(o->oPosY > gMarioState->pos[1] && o->oTimer < 25)
//             o->oTimer = 25;
//     } else {
//         o->oAction = BLOOPER_FALL;
//     }
// }

// void blooper_act_fall(void) {
//     o->oForwardVel = 0.0f;
//     if((o->oPosY > gMarioState->pos[1] - 250.0f && o->oPosY > o->oFloorHeight + 50) || o->oTimer < 30) {
//         if(o->oTimer < 10)
//             o->oPosY -= o->oTimer;
//         else 
//             o->oPosY -= 15.0f;
//     } else {
//         o->oAction = BLOOPER_IDLE;
//     }
// }

// void bhv_blooper_update(void) {
//     o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 
//             0x400);

//     switch(o->oAction) {
//         case BLOOPER_IDLE:
//             blooper_act_idle();
//             break;
//         case BLOOPER_RISE:
//             blooper_act_rise();
//             break;
//         case BLOOPER_FALL:
//             blooper_act_fall();
//             break;
//     }

//     cur_obj_move_xz_using_fvel_and_yaw();

//     if(o->oAction != BLOOPER_RISE) {
//         if(o->header.gfx.scale[0] < 1.0f)
//             o->header.gfx.scale[0] = o->header.gfx.scale[2] = o->header.gfx.scale[0] + 0.025f;
//         else
//             o->header.gfx.scale[0] = o->header.gfx.scale[2] = 1.0f;
//     }

//     o->oFloorHeight = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
//     if (o->oPosY < o->oFloorHeight + 50) {
//         o->oPosY = o->oFloorHeight + 50;
//     }


//     ceilHeight = find_ceil(o->oPosX, o->oPosY, o->oPosZ, &surface);
//     if (o->oPosY > ceilHeight - 250)
//         o->oPosY = ceilHeight - 250;
//     o->oInteractStatus = 0;
// }
