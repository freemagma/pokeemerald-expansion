#include "global.h"
#include "random.h"
#include "pokemon.h"
#include "overworld.h"

#include "routing.h"

struct RouteNode {
    u8 options[2];
};

#define MAX_ROUTE_LENGTH 20
static EWRAM_DATA u16 sRouteIndex = 0;
static EWRAM_DATA struct RouteNode sRoute[MAX_ROUTE_LENGTH] = {0};

static const struct RouteNode sDTutorialA1Route[10] = {
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_GIFT1, 0}},
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_ENCOUNTER1, 0}},
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_BATTLE1, 0}},
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_BATTLE1, 0}},
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_SHOP1_FORK, 0}},
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_BATTLE1_FORK, MAP_DUNGEON_TUTORIAL_ACT1_ENCOUNTER1_FORK}},
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_BATTLE1, MAP_DUNGEON_TUTORIAL_ACT1_ENCOUNTER1}},
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_BATTLE1, 0}},
{.options = {MAP_DUNGEON_TUTORIAL_ACT1_SHOP1, 0}},
{0}
};

void GenerateRoute(void)
{
    u16 i;
    for (i = 0; i < ARRAY_COUNT(sDTutorialA1Route); i++) {
        sRoute[i] = sDTutorialA1Route[i];
    }
    sRouteIndex = 0;
}

bool8 IsCurrentlyRouting(void)
{
    return sRoute[sRouteIndex].options[0] != 0;
}

const struct WarpEvent* SetWarpDestinationRouting(u8 warpEventId)
{
    u8 map;
    const struct MapHeader *header;
    u8 warpOptionIndex = warpEventId;

    if (warpOptionIndex > 0)
        warpOptionIndex--;

    map = sRoute[sRouteIndex++].options[warpOptionIndex];
    header = Overworld_GetMapHeaderByGroupAndId(map >> 8, map & 0xFF);

    return &header->events->warps[0];
}
