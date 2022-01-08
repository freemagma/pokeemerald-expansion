#ifndef GUARD_ROUTING_H
#define GUARD_ROUTING_H

#define DTA1(mapend) (MAP_DUNGEON_TUTORIAL_ACT1_##mapend)

struct RouteOption {
    u16 map;
    const u8 *string;
    u8 param;
};

void DungeonTutorial_GenerateRoute(void);
bool8 IsCurrentlyRouting(void);
u8 GetRouteParam(void);
const struct WarpEvent* SetWarpDestinationRouting(u8 warpEventId);

#endif // GUARD_ROUTING_H
