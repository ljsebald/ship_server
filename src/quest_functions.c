/*
    Sylverant Ship Server
    Copyright (C) 2019 Lawrence Sebald

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License version 3
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <time.h>
#include <stdint.h>

#include "clients.h"
#include "lobby.h"
#include "quest_functions.h"
#include "ship_packets.h"

static uint32_t get_section_id(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 1)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    /* Are we requesting everyone or just one person? */
    if(c->q_stack[3] == 0xFFFFFFFF) {
        if(c->q_stack[2] != 4)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255 || c->q_stack[5] > 255 ||
           c->q_stack[6] > 255 || c->q_stack[7] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[0])
            send_sync_register(c, c->q_stack[4],
                               l->clients[0]->pl->v1.section);
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        if(l->clients[1])
            send_sync_register(c, c->q_stack[5],
                               l->clients[1]->pl->v1.section);
        else
            send_sync_register(c, c->q_stack[5], 0xFFFFFFFF);

        if(l->clients[2])
            send_sync_register(c, c->q_stack[6],
                               l->clients[2]->pl->v1.section);
        else
            send_sync_register(c, c->q_stack[6], 0xFFFFFFFF);

        if(l->clients[3])
            send_sync_register(c, c->q_stack[7],
                               l->clients[3]->pl->v1.section);
        else
            send_sync_register(c, c->q_stack[7], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else if(c->q_stack[3] < 4) {
        if(c->q_stack[2] != 1)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[c->q_stack[3]])
            send_sync_register(c, c->q_stack[4],
                               l->clients[c->q_stack[3]]->pl->v1.section);
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else {
        return QUEST_FUNC_RET_INVALID_ARG;
    }
}

uint32_t get_time(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 0)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    if(c->q_stack[2] != 1)
        return QUEST_FUNC_RET_BAD_RET_COUNT;

    if(c->q_stack[3] > 255)
        return QUEST_FUNC_RET_INVALID_REGISTER;

    send_sync_register(c, c->q_stack[3], (uint32_t)time(NULL));
    return QUEST_FUNC_RET_NO_ERROR;
}

uint32_t get_client_count(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 0)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    if(c->q_stack[2] != 1)
        return QUEST_FUNC_RET_BAD_RET_COUNT;

    if(c->q_stack[3] > 255)
        return QUEST_FUNC_RET_INVALID_REGISTER;

    send_sync_register(c, c->q_stack[3], l->num_clients);
    return QUEST_FUNC_RET_NO_ERROR;
}

static uint32_t get_char_class(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 1)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    /* Are we requesting everyone or just one person? */
    if(c->q_stack[3] == 0xFFFFFFFF) {
        if(c->q_stack[2] != 4)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255 || c->q_stack[5] > 255 ||
           c->q_stack[6] > 255 || c->q_stack[7] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[0])
            send_sync_register(c, c->q_stack[4],
                               l->clients[0]->pl->v1.ch_class);
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        if(l->clients[1])
            send_sync_register(c, c->q_stack[5],
                               l->clients[1]->pl->v1.ch_class);
        else
            send_sync_register(c, c->q_stack[5], 0xFFFFFFFF);

        if(l->clients[2])
            send_sync_register(c, c->q_stack[6],
                               l->clients[2]->pl->v1.ch_class);
        else
            send_sync_register(c, c->q_stack[6], 0xFFFFFFFF);

        if(l->clients[3])
            send_sync_register(c, c->q_stack[7],
                               l->clients[3]->pl->v1.ch_class);
        else
            send_sync_register(c, c->q_stack[7], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else if(c->q_stack[3] < 4) {
        if(c->q_stack[2] != 1)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[c->q_stack[3]])
            send_sync_register(c, c->q_stack[4],
                               l->clients[c->q_stack[3]]->pl->v1.ch_class);
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else {
        return QUEST_FUNC_RET_INVALID_ARG;
    }
}

static int genders[12] = { 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 };
static int races[12] = { 0, 1, 2, 0, 2, 2, 0, 1, 1, 2, 0, 0 };
static int jobs[12] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 2, 1 };

#define ATTR(x, y) (((x) < 12) ? y[(x)] : -1)
#define GENDER(x) ATTR((x), genders)
#define RACE(x) ATTR((x), races)
#define JOB(x) ATTR((x), jobs)

static uint32_t get_char_gender(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 1)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    /* Are we requesting everyone or just one person? */
    if(c->q_stack[3] == 0xFFFFFFFF) {
        if(c->q_stack[2] != 4)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255 || c->q_stack[5] > 255 ||
           c->q_stack[6] > 255 || c->q_stack[7] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[0])
            send_sync_register(c, c->q_stack[4],
                               GENDER(l->clients[0]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        if(l->clients[1])
            send_sync_register(c, c->q_stack[5],
                               GENDER(l->clients[1]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[5], 0xFFFFFFFF);

        if(l->clients[2])
            send_sync_register(c, c->q_stack[6],
                               GENDER(l->clients[2]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[6], 0xFFFFFFFF);

        if(l->clients[3])
            send_sync_register(c, c->q_stack[7],
                               GENDER(l->clients[3]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[7], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else if(c->q_stack[3] < 4) {
        int cl = c->q_stack[3];

        if(c->q_stack[2] != 1)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[cl])
            send_sync_register(c, c->q_stack[4],
                               GENDER(l->clients[cl]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else {
        return QUEST_FUNC_RET_INVALID_ARG;
    }
}

static uint32_t get_char_race(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 1)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    /* Are we requesting everyone or just one person? */
    if(c->q_stack[3] == 0xFFFFFFFF) {
        if(c->q_stack[2] != 4)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255 || c->q_stack[5] > 255 ||
           c->q_stack[6] > 255 || c->q_stack[7] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[0])
            send_sync_register(c, c->q_stack[4],
                               RACE(l->clients[0]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        if(l->clients[1])
            send_sync_register(c, c->q_stack[5],
                               RACE(l->clients[1]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[5], 0xFFFFFFFF);

        if(l->clients[2])
            send_sync_register(c, c->q_stack[6],
                               RACE(l->clients[2]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[6], 0xFFFFFFFF);

        if(l->clients[3])
            send_sync_register(c, c->q_stack[7],
                               RACE(l->clients[3]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[7], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else if(c->q_stack[3] < 4) {
        int cl = c->q_stack[3];

        if(c->q_stack[2] != 1)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[cl])
            send_sync_register(c, c->q_stack[4],
                               RACE(l->clients[cl]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else {
        return QUEST_FUNC_RET_INVALID_ARG;
    }
}

static uint32_t get_char_job(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 1)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    /* Are we requesting everyone or just one person? */
    if(c->q_stack[3] == 0xFFFFFFFF) {
        if(c->q_stack[2] != 4)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255 || c->q_stack[5] > 255 ||
           c->q_stack[6] > 255 || c->q_stack[7] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[0])
            send_sync_register(c, c->q_stack[4],
                               JOB(l->clients[0]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        if(l->clients[1])
            send_sync_register(c, c->q_stack[5],
                               JOB(l->clients[1]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[5], 0xFFFFFFFF);

        if(l->clients[2])
            send_sync_register(c, c->q_stack[6],
                               JOB(l->clients[2]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[6], 0xFFFFFFFF);

        if(l->clients[3])
            send_sync_register(c, c->q_stack[7],
                               JOB(l->clients[3]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[7], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else if(c->q_stack[3] < 4) {
        int cl = c->q_stack[3];

        if(c->q_stack[2] != 1)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[cl])
            send_sync_register(c, c->q_stack[4],
                               JOB(l->clients[cl]->pl->v1.ch_class));
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else {
        return QUEST_FUNC_RET_INVALID_ARG;
    }
}

static uint32_t get_client_floor(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 1)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    /* Are we requesting everyone or just one person? */
    if(c->q_stack[3] == 0xFFFFFFFF) {
        if(c->q_stack[2] != 4)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255 || c->q_stack[5] > 255 ||
           c->q_stack[6] > 255 || c->q_stack[7] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[0])
            send_sync_register(c, c->q_stack[4], l->clients[0]->cur_area);
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        if(l->clients[1])
            send_sync_register(c, c->q_stack[5], l->clients[1]->cur_area);
        else
            send_sync_register(c, c->q_stack[5], 0xFFFFFFFF);

        if(l->clients[2])
            send_sync_register(c, c->q_stack[6], l->clients[2]->cur_area);
        else
            send_sync_register(c, c->q_stack[6], 0xFFFFFFFF);

        if(l->clients[3])
            send_sync_register(c, c->q_stack[7], l->clients[3]->cur_area);
        else
            send_sync_register(c, c->q_stack[7], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else if(c->q_stack[3] < 4) {
        int cl = c->q_stack[3];

        if(c->q_stack[2] != 1)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[cl])
            send_sync_register(c, c->q_stack[4], l->clients[cl]->cur_area);
        else
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else {
        return QUEST_FUNC_RET_INVALID_ARG;
    }
}

static uint32_t get_client_position(ship_client_t *c, lobby_t *l) {
    if(c->q_stack[1] != 1)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    /* Are we requesting everyone or just one person? */
    if(c->q_stack[3] == 0xFFFFFFFF) {
        if(c->q_stack[2] != 4)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255 || c->q_stack[5] > 255 ||
           c->q_stack[6] > 255 || c->q_stack[7] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[0]) {
            send_sync_register(c, c->q_stack[4], (uint32_t)l->clients[0]->x);
            send_sync_register(c, c->q_stack[4] + 1,
                               (uint32_t)l->clients[0]->y);
            send_sync_register(c, c->q_stack[4] + 2,
                               (uint32_t)l->clients[0]->z);
        }
        else {
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[4] + 1, 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[4] + 2, 0xFFFFFFFF);
        }

        if(l->clients[1]) {
            send_sync_register(c, c->q_stack[5], (uint32_t)l->clients[1]->x);
            send_sync_register(c, c->q_stack[5] + 1,
                               (uint32_t)l->clients[1]->y);
            send_sync_register(c, c->q_stack[5] + 2,
                               (uint32_t)l->clients[1]->z);
        }
        else {
            send_sync_register(c, c->q_stack[5], 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[5] + 1, 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[5] + 2, 0xFFFFFFFF);
        }

        if(l->clients[2]) {
            send_sync_register(c, c->q_stack[6], (uint32_t)l->clients[2]->x);
            send_sync_register(c, c->q_stack[6] + 1,
                               (uint32_t)l->clients[2]->y);
            send_sync_register(c, c->q_stack[6] + 2,
                               (uint32_t)l->clients[2]->z);
        }
        else {
            send_sync_register(c, c->q_stack[6], 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[6] + 1, 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[6] + 2, 0xFFFFFFFF);
        }

        if(l->clients[3]) {
            send_sync_register(c, c->q_stack[7], (uint32_t)l->clients[3]->x);
            send_sync_register(c, c->q_stack[7] + 1,
                               (uint32_t)l->clients[3]->y);
            send_sync_register(c, c->q_stack[7] + 2,
                               (uint32_t)l->clients[3]->z);
        }
        else {
            send_sync_register(c, c->q_stack[7], 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[7] + 1, 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[7] + 2, 0xFFFFFFFF);
        }

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else if(c->q_stack[3] < 4) {
        int cl = c->q_stack[3];

        if(c->q_stack[2] != 1)
            return QUEST_FUNC_RET_BAD_RET_COUNT;

        if(c->q_stack[4] > 255)
            return QUEST_FUNC_RET_INVALID_REGISTER;

        if(l->clients[cl]) {
            send_sync_register(c, c->q_stack[4], (uint32_t)l->clients[cl]->x);
            send_sync_register(c, c->q_stack[4] + 1,
                               (uint32_t)l->clients[cl]->y);
            send_sync_register(c, c->q_stack[4] + 2,
                               (uint32_t)l->clients[cl]->z);
        }
        else {
            send_sync_register(c, c->q_stack[4], 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[4] + 1, 0xFFFFFFFF);
            send_sync_register(c, c->q_stack[4] + 2, 0xFFFFFFFF);
        }

        /* Done. */
        return QUEST_FUNC_RET_NO_ERROR;
    }
    else {
        return QUEST_FUNC_RET_INVALID_ARG;
    }
}

static uint32_t get_random_integer(ship_client_t *c, lobby_t *l) {
    uint32_t min, max, rnd;

    if(c->q_stack[1] != 2)
        return QUEST_FUNC_RET_BAD_ARG_COUNT;

    if(c->q_stack[2] != 1)
        return QUEST_FUNC_RET_BAD_RET_COUNT;

    if(c->q_stack[5] > 255)
        return QUEST_FUNC_RET_INVALID_REGISTER;

    min = c->q_stack[3];
    max = c->q_stack[4];

    if(min >= max)
        return QUEST_FUNC_RET_INVALID_ARG;

    max -= min;

    rnd = (uint32_t)(mt19937_genrand_int32(&l->block->rng) %
                     ((uint64_t)max + 1) + min);

    send_sync_register(c, c->q_stack[5], rnd);
    return QUEST_FUNC_RET_NO_ERROR;
}

uint32_t quest_function_dispatch(ship_client_t *c, lobby_t *l) {
    /* Call the requested function... */
    switch(c->q_stack[0]) {
        case QUEST_FUNC_GET_SECTION:
            return get_section_id(c, l);

        case QUEST_FUNC_TIME:
            return get_time(c, l);

        case QUEST_FUNC_CLIENT_COUNT:
            return get_client_count(c, l);

        case QUEST_FUNC_GET_CLASS:
            return get_char_class(c, l);

        case QUEST_FUNC_GET_GENDER:
            return get_char_gender(c, l);

        case QUEST_FUNC_GET_RACE:
            return get_char_race(c, l);

        case QUEST_FUNC_GET_JOB:
            return get_char_job(c, l);

        case QUEST_FUNC_GET_FLOOR:
            return get_client_floor(c, l);

        case QUEST_FUNC_GET_POSITION:
            return get_client_position(c, l);

        case QUEST_FUNC_GET_RANDOM:
            return get_random_integer(c, l);

        default:
            return QUEST_FUNC_RET_INVALID_FUNC;
    }
}
