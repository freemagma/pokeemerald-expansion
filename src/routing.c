#include "global.h"
#include "random.h"
#include "pokemon.h"
#include "overworld.h"
#include "strings.h"
#include "string_util.h"

#include "routing.h"

static u16 ForkMap(u16);
static void ForkMapsInRoute(void);

#define MAX_ROUTE_LENGTH 30
static EWRAM_DATA u16 sRouteIndex = 0;
static EWRAM_DATA u8 sRouteParam = 0;
static EWRAM_DATA struct RouteOption sRoute[MAX_ROUTE_LENGTH][2] = {0};

static const struct RouteOption routeNone = {0};

void DungeonTutorial_GenerateRoute(void)
{
    const struct RouteOption battle = {.map = DTA1(BATTLE1), .string = gText_BattleRoom};
    const struct RouteOption eliteBattle = {.map = DTA1(ELITE_BATTLE1), .string = gText_EliteBattleRoom};
    const struct RouteOption boss = {.map = DTA1(BOSS), .string = NULL};
    const struct RouteOption gift = {.map = DTA1(GIFT1), .string = gText_GiftRoom};
    const struct RouteOption encounter = {.map = DTA1(ENCOUNTER1), .string = gText_EncounterRoom};
    const struct RouteOption shop = {.map = DTA1(SHOP1), .string = gText_ShopRoom};

    u16 i = 0;
    u16 temp;

    ClearRoute();

    sRoute[i++][0] = gift;
    sRoute[i++][0] = encounter;
    sRoute[i++][0] = battle;
    sRoute[i++][0] = shop;

    sRoute[i][0] = battle; sRoute[i][0].param = 1;
    sRoute[i++][1] = encounter;
    sRoute[i][0] = battle; sRoute[i++][0].param = 1;
    sRoute[i][0] = battle; sRoute[i++][0].param = 1;

    sRoute[i][0] = encounter; sRoute[i++][1] = shop;

    sRoute[i][0] = battle; sRoute[i++][0].param = 1;
    sRoute[i++][0] = eliteBattle;

    sRoute[i++][0] = shop;
    sRoute[i++][0] = boss;

    ForkMapsInRoute();
}

bool8 IsRoutedWarp(u8 warpEventId)
{
    return sRoute[sRouteIndex][0].map != 0 && warpEventId != 0;
}

u8 GetRouteParam(void) {
    return sRouteParam;
}

const struct WarpEvent* SetWarpDestinationRouting(u8 warpEventId)
{
    u16 map;
    const struct MapHeader *header;
    u8 warpOptionIndex;

    warpOptionIndex = warpEventId - 1;

    map = sRoute[sRouteIndex][warpOptionIndex].map;
    sRouteParam = sRoute[sRouteIndex][warpOptionIndex].param;
    sRouteIndex++;

    header = Overworld_GetMapHeaderByGroupAndId(map >> 8, map & 0xFF);

    return &header->events->warps[0];
}

void BufferRouteText(void)
{
    StringCopy(gStringVar1, sRoute[sRouteIndex][0].string);
    StringCopy(gStringVar2, sRoute[sRouteIndex][1].string);
}

void ClearRoute(void) {
    u16 i;
    for (i = 0; i < MAX_ROUTE_LENGTH; i++) {
        sRoute[i][0] = routeNone;
        sRoute[i][1] = routeNone;
    }
    sRouteIndex = 0;
    sRouteParam = 0;
}

static void ForkMapsInRoute(void) {
    u16 i;
    for (i = 0; sRoute[i][0].map; i++) {
        if (sRoute[i + 1][1].map) {
            sRoute[i][0].map = ForkMap(sRoute[i][0].map);
            if (sRoute[i][1].map)
                sRoute[i][1].map = ForkMap(sRoute[i][1].map);
        }
    }
}

static u16 ForkMap(u16 map) {
    switch (map) {
        case DTA1(ENCOUNTER1):
            return DTA1(ENCOUNTER1_FORK);
        case DTA1(BATTLE1):
            return DTA1(BATTLE1_FORK);
        case DTA1(SHOP1):
            return DTA1(SHOP1_FORK);
        default:
            return MAP_NONE;
    }
}
