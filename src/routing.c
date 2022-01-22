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
        case DTUA1(ENCOUNTER1):
            return DTUA1(ENCOUNTER1_FORK);
        case DTUA1(BATTLE1):
            return DTUA1(BATTLE1_FORK);
        case DTUA1(SHOP1):
            return DTUA1(SHOP1_FORK);
        case DEDA1(ENCOUNTER1):
            return DEDA1(ENCOUNTER1_FORK);
        case DEDA1(BATTLE1):
            return DEDA1(BATTLE1_FORK);
        case DEDA1(SHOP1):
            return DEDA1(SHOP1_FORK);
        case DEDA1(GIFT1):
            return DEDA1(GIFT1_FORK);
        case DEDA1(ELITE_BATTLE1):
            return DEDA1(ELITE_BATTLE1_FORK);
        default:
            return MAP_NONE;
    }
}

void DungeonTutorial_GenerateRoute(void)
{
    const struct RouteOption battle = {.map = DTUA1(BATTLE1), .string = gText_BattleRoom};
    const struct RouteOption eliteBattle = {.map = DTUA1(ELITE_BATTLE1), .string = gText_EliteBattleRoom};
    const struct RouteOption boss = {.map = DTUA1(BOSS), .string = NULL};
    const struct RouteOption gift = {.map = DTUA1(GIFT1), .string = gText_GiftRoom};
    const struct RouteOption encounter = {.map = DTUA1(ENCOUNTER1), .string = gText_EncounterRoom};
    const struct RouteOption shop = {.map = DTUA1(SHOP1), .string = gText_ShopRoom};

    u16 i = 0;

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

void DungeonEden_GenerateRoute(void) {
    const struct RouteOption battle = {.map = DEDA1(BATTLE1), .string = gText_BattleRoom};
    const struct RouteOption eliteBattle = {.map = DEDA1(ELITE_BATTLE1), .string = gText_EliteBattleRoom};
    const struct RouteOption boss = {.map = DEDA1(BOSS), .string = NULL};
    const struct RouteOption gift = {.map = DEDA1(GIFT1), .string = gText_GiftRoom};
    const struct RouteOption encounter = {.map = DEDA1(ENCOUNTER1), .string = gText_EncounterRoom};
    const struct RouteOption shop = {.map = DEDA1(SHOP1), .string = gText_ShopRoom};

    u16 i = 0;
    u16 j = 0;
    u16 groupedFloors;
    u16 specialFloor;

    ClearRoute();

    sRoute[i++][0] = gift;

    groupedFloors = 3;
    specialFloor = 1 + Random() % (groupedFloors - 1);
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            sRoute[i][0] = encounter;
            sRoute[i][1] = battle;
            sRoute[i][1].param = 0;
        } else {
            sRoute[i][0] = battle;
            sRoute[i][0].param = 0;
        }
    }

    sRoute[i++][0] = shop;

    groupedFloors = 3 + (Random() % 2);
    specialFloor = Random() % (groupedFloors - 1);
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            sRoute[i][0] = encounter;
            sRoute[i][1] = eliteBattle;
        } else {
            sRoute[i][0] = battle;
            sRoute[i][0].param = 1;
        }
    }

    sRoute[i][0] = encounter;
    sRoute[i++][1] = shop;

    groupedFloors = 7 - groupedFloors;
    specialFloor = Random() % groupedFloors;
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            sRoute[i][0] = eliteBattle;
        } else {
            sRoute[i][0] = battle;
            sRoute[i][0].param = 1;
        }
    }

    sRoute[i++][0] = shop;
    sRoute[i++][0] = boss;

    ForkMapsInRoute();
}
