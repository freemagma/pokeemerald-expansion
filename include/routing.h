#ifndef GUARD_ROUTING_H
#define GUARD_ROUTING_H

void GenerateRoute(void);
bool8 IsCurrentlyRouting(void);
const struct WarpEvent* SetWarpDestinationRouting(u8 warpEventId);

#endif // GUARD_ROUTING_H
