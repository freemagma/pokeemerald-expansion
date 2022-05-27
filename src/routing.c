#include "global.h"
#include "random.h"
#include "pokemon.h"
#include "overworld.h"
#include "strings.h"
#include "string_util.h"

#include "routing.h"

#define G_ROUTE gSaveBlock1Ptr->route
#define G_ROUTE_IX gSaveBlock1Ptr->routeIndex
#define G_ROUTE_PARAM gSaveBlock1Ptr->routeParam

static u16 ForkMap(u16);
static void ForkMapsInRoute(void);

static const struct RouteOption routeNone = {0};

bool8 IsRoutedWarp(u8 warpEventId)
{
    return G_ROUTE[G_ROUTE_IX][0].map != 0 && warpEventId != 0;
}

u8 GetRouteParam(void) {
    return G_ROUTE_PARAM;
}

const struct WarpEvent* SetWarpDestinationRouting(u8 warpEventId)
{
    u16 map;
    const struct MapHeader *header;
    u8 warpOptionIndex;

    warpOptionIndex = warpEventId - 1;

    map = G_ROUTE[G_ROUTE_IX][warpOptionIndex].map;
    G_ROUTE_PARAM = G_ROUTE[G_ROUTE_IX][warpOptionIndex].param;
    G_ROUTE_IX++;

    header = Overworld_GetMapHeaderByGroupAndId(map >> 8, map & 0xFF);

    return &header->events->warps[0];
}

void BufferRouteText(void)
{
    StringCopy(gStringVar1, G_ROUTE[G_ROUTE_IX][0].string);
    StringCopy(gStringVar2, G_ROUTE[G_ROUTE_IX][1].string);
}

void ClearRoute(void) {
    u16 i;
    for (i = 0; i < MAX_ROUTE_LENGTH; i++) {
        G_ROUTE[i][0] = routeNone;
        G_ROUTE[i][1] = routeNone;
    }
    G_ROUTE_IX = 0;
    G_ROUTE_PARAM = 0;
}

static void ForkMapsInRoute(void) {
    u16 i;
    for (i = 0; G_ROUTE[i][0].map; i++) {
        if (G_ROUTE[i + 1][1].map) {
            G_ROUTE[i][0].map = ForkMap(G_ROUTE[i][0].map);
            if (G_ROUTE[i][1].map)
                G_ROUTE[i][1].map = ForkMap(G_ROUTE[i][1].map);
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
        case DEDA2(ENCOUNTER1):
            return DEDA2(ENCOUNTER1_FORK);
        case DEDA2(BATTLE1):
            return DEDA2(BATTLE1_FORK);
        case DEDA2(SHOP1):
            return DEDA2(SHOP1_FORK);
        case DEDA2(GIFT1):
            return DEDA2(GIFT1_FORK);
        case DEDA2(ELITE_BATTLE1):
            return DEDA2(ELITE_BATTLE1_FORK);
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

    G_ROUTE[i++][0] = gift;
    G_ROUTE[i++][0] = encounter;
    G_ROUTE[i++][0] = battle;
    G_ROUTE[i++][0] = shop;

    G_ROUTE[i][0] = battle; G_ROUTE[i][0].param = 1;
    G_ROUTE[i++][1] = encounter;
    G_ROUTE[i][0] = battle; G_ROUTE[i++][0].param = 1;
    G_ROUTE[i][0] = battle; G_ROUTE[i++][0].param = 1;

    G_ROUTE[i][0] = encounter; G_ROUTE[i++][1] = shop;

    G_ROUTE[i][0] = battle; G_ROUTE[i++][0].param = 1;
    G_ROUTE[i++][0] = eliteBattle;

    G_ROUTE[i++][0] = shop;
    G_ROUTE[i++][0] = boss;

    ForkMapsInRoute();
}

void DungeonEden_Act1_GenerateRoute(void) {
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

    G_ROUTE[i++][0] = gift;
    G_ROUTE[i++][0] = encounter;

    groupedFloors = 3;
    specialFloor = 1 + Random() % (groupedFloors - 1);
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            G_ROUTE[i][0] = encounter;
            G_ROUTE[i][1] = battle;
            G_ROUTE[i][1].param = 0;
        } else {
            G_ROUTE[i][0] = battle;
            G_ROUTE[i][0].param = 0;
        }
    }

    G_ROUTE[i++][0] = shop;

    groupedFloors = 3;
    specialFloor = Random() % groupedFloors;
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            G_ROUTE[i][0] = encounter;
            G_ROUTE[i][1] = battle;
            G_ROUTE[i][1].param = 1;
        } else {
            G_ROUTE[i][0] = battle;
            G_ROUTE[i][0].param = 1;
        }
    }

    G_ROUTE[i][0] = encounter;
    G_ROUTE[i++][1] = eliteBattle;

    G_ROUTE[i++][0] = shop;

    groupedFloors = 4;
    specialFloor = Random() % groupedFloors;
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            G_ROUTE[i][0] = eliteBattle;
        } else {
            G_ROUTE[i][0] = battle;
            G_ROUTE[i][0].param = 2;
        }
    }

    G_ROUTE[i++][0] = encounter;
    G_ROUTE[i++][0] = shop;
    G_ROUTE[i++][0] = boss;

    ForkMapsInRoute();
}

void DungeonEden_Act2_GenerateRoute(void) {
    const struct RouteOption battle = {.map = DEDA2(BATTLE1), .string = gText_BattleRoom};
    const struct RouteOption eliteBattle = {.map = DEDA2(ELITE_BATTLE1), .string = gText_EliteBattleRoom};
    const struct RouteOption boss = {.map = DEDA2(BOSS), .string = NULL};
    const struct RouteOption gift = {.map = DEDA2(GIFT1), .string = gText_GiftRoom};
    const struct RouteOption encounter = {.map = DEDA2(ENCOUNTER1), .string = gText_EncounterRoom};
    const struct RouteOption shop = {.map = DEDA2(SHOP1), .string = gText_ShopRoom};

    u16 i = 0;
    u16 j = 0;
    u16 groupedFloors;
    u16 specialFloor;

    ClearRoute();

    G_ROUTE[i++][0] = gift;
    G_ROUTE[i++][0] = encounter;
    G_ROUTE[i++][0] = shop;

    groupedFloors = 4;
    specialFloor = 1 + Random() % (groupedFloors - 1);
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            G_ROUTE[i][0] = encounter;
        } else {
            G_ROUTE[i][0] = battle;
            G_ROUTE[i][0].param = 0;
        }
    }

    G_ROUTE[i++][0] = shop;

    groupedFloors = 3;
    specialFloor = Random() % groupedFloors;
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            G_ROUTE[i][0] = encounter;
            G_ROUTE[i][1] = battle;
            G_ROUTE[i][1].param = 1;
        } else {
            G_ROUTE[i][0] = battle;
            G_ROUTE[i][0].param = 1;
        }
    }

    G_ROUTE[i][0] = encounter;
    G_ROUTE[i++][1] = eliteBattle;

    G_ROUTE[i++][0] = shop;

    groupedFloors = 4;
    specialFloor = Random() % groupedFloors;
    for (j = 0; j < groupedFloors; j++, i++) {
        if (j == specialFloor) {
            G_ROUTE[i][0] = eliteBattle;
        } else {
            G_ROUTE[i][0] = battle;
            G_ROUTE[i][0].param = 2;
        }
    }

    G_ROUTE[i++][0] = shop;
    G_ROUTE[i++][0] = boss;

    ForkMapsInRoute();
}
