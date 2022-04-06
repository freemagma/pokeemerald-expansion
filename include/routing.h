#ifndef GUARD_ROUTING_H
#define GUARD_ROUTING_H

#define DTUA1(mapend) (MAP_DUNGEON_TUTORIAL_ACT1_##mapend)
#define DEDA1(mapend) (MAP_DUNGEON_EDEN_ACT1_##mapend)

void DungeonTutorial_GenerateRoute(void);
bool8 IsRoutedWarp(u8);
u8 GetRouteParam(void);
void ClearRoute(void);
const struct WarpEvent* SetWarpDestinationRouting(u8 warpEventId);

#endif // GUARD_ROUTING_H
