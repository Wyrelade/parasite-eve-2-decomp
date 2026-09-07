#include "common.h"
#include "rooms/room_common.h"
#include "gameplay/3CD8.h"
#include "gameplay/gameplay.h"
#include "main/task.h"
#include "psyq/libgte.h"
#include "psyq/inline_c.h"

#define gte_mvmva_real() __asm__ volatile("nop; nop; .word 0x4A486012")
#define gte_gpf12_real() __asm__ volatile("nop; nop; .word 0x4B98003D")

INCLUDE_ASM("rooms/nonmatchings/shelter_b1_control_room_access_tunnel/shelter_b1_control_room_access_tunnel_4", func_shelter_b1_control_room_access_tunnel_8018026C);

void func_shelter_b1_control_room_access_tunnel_801807C4(Task* task)
{
    register RoomEffWork* work asm("s0");
    GsCOORDINATE2*        coord;
    GsCOORDINATE2*        target;
    SVECTOR*              sv;
    VECTOR                delta;
    register s32          var_v0 asm("v0");

    work   = task->spawnArg2;
    coord  = ((TmdObject*)task->extra)->field_8;
    target = (GsCOORDINATE2*)task->spawnArg1;
    if (Gp_State1C->field_4 == 0) {
        work->field_22++;
        switch (task->state) {
            case 0:
                delta.vx = target->workm.t[0] - coord->workm.t[0];
                delta.vy = target->workm.t[1] - coord->workm.t[1];
                delta.vz = target->workm.t[2] - coord->workm.t[2];
                ApplyTransposeMatrixLV(&coord->workm, &delta, &delta);
                work->field_18 = delta.vx;
                work->field_1A = delta.vy;
                work->field_1C = delta.vz;
                gte_SetRotMatrix(&coord->coord);
                sv = (SVECTOR*)&work->field_18;
                gte_ldv0(sv);
                gte_mvmva_real();
                gte_stsv(sv);
                gte_lddp(0xCC);
                gte_ldsv(sv);
                gte_gpf12_real();
                gte_stsv(sv);
                USE_REG(work);
                task->state = 1;
                return;
            case 1:
                coord->coord.t[0] += (s16)work->field_18;
                coord->coord.t[1] += (s16)work->field_1A;
                coord->coord.t[2] += (s16)work->field_1C;
                coord->flg         = 0;
                Gp_UpdateCoord(coord);
                if (work->field_22 & 1) {
                    work->field_20++;
                    Room_Draw14(coord, (s16)work->field_20, 0x200, 0x80);
                }
                var_v0 = (s16)work->field_22 < 0x14;
                break;
            default:
                return;
        }
    } else {
        var_v0 = Gp_State1C->field_4 < 4;
    }
    if (var_v0 == 0) {
        Gp_ReleaseState1CMem(work, task);
    }
}

INCLUDE_RODATA("rooms/nonmatchings/shelter_b1_control_room_access_tunnel/shelter_b1_control_room_access_tunnel_4", D_shelter_b1_control_room_access_tunnel_8017D5E4);
