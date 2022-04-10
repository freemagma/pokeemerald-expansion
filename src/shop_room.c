#include "global.h"
#include "shop.h"
#include "random.h"
#include "event_data.h"
#include "constants/items.h"

#include "shop_room.h"


#define G_RANDOM_SHOP gSaveBlock1Ptr->randomShopItems

#define DEFAULT_SHOP_SIZE 7

static const struct ItemPrice sItemPriceNone = {0};

static const struct ItemPrice sBasicItems[] = {
{.itemId = ITEM_POKE_BALL, .price = 20},
{.itemId = ITEM_MAX_POTION, .price = 50},
{.itemId = ITEM_FULL_HEAL, .price = 25},
{.itemId = ITEM_SITRUS_BERRY, .price = 100},
{.itemId = ITEM_LUM_BERRY, .price = 50},
{.itemId = ITEM_RARE_CANDY, .price = 10},
{0}
};

static const struct ItemPrice sDTutorialA1ItemPool[] = {
{.itemId = ITEM_TM09_BULLET_SEED, .price = 400},
{.itemId = ITEM_TM03_WATER_PULSE, .price = 400},
{.itemId = ITEM_TM28_DIG, .price = 500},
{.itemId = ITEM_TM35_FLAMETHROWER, .price = 800},
{.itemId = ITEM_TM13_ICE_BEAM, .price = 800},
{.itemId = ITEM_TM24_THUNDERBOLT, .price = 800},
{.itemId = ITEM_TM31_BRICK_BREAK, .price = 600},
{.itemId = ITEM_PROTEIN, .price = 100},
{.itemId = ITEM_CALCIUM, .price = 100},
{.itemId = ITEM_CARBOS, .price = 100},
{.itemId = ITEM_ZINC, .price = 100},
{.itemId = ITEM_HP_UP, .price = 100},
{.itemId = ITEM_IRON, .price = 100},
{.itemId = ITEM_LEFTOVERS, .price = 600},
{.itemId = ITEM_EXPERT_BELT, .price = 300},
{.itemId = ITEM_SOFT_SAND, .price = 200},
{.itemId = ITEM_BRIGHT_POWDER, .price = 200},
{.itemId = ITEM_KINGS_ROCK, .price = 200},
{.itemId = ITEM_WATER_STONE, .price = 900},
{.itemId = ITEM_MOON_STONE, .price = 900},
{.itemId = ITEM_REVIVE, .price = 2500},
{0}
};

static const struct ItemPrice sDEdenA1ItemPool[] = {
{.itemId = ITEM_PROTEIN, .price = 100},
{.itemId = ITEM_CALCIUM, .price = 100},
{.itemId = ITEM_CARBOS, .price = 100},
{.itemId = ITEM_ZINC, .price = 100},
{.itemId = ITEM_HP_UP, .price = 100},
{.itemId = ITEM_IRON, .price = 100},
{.itemId = ITEM_LEFTOVERS, .price = 600},
{.itemId = ITEM_FOCUS_SASH, .price = 500},
{.itemId = ITEM_MIRACLE_SEED, .price = 200},
{.itemId = ITEM_MYSTIC_WATER, .price = 200},
{.itemId = ITEM_CHARCOAL, .price = 200},
{.itemId = ITEM_QUICK_CLAW, .price = 200},
{.itemId = ITEM_SHINY_STONE, .price = 800},
{.itemId = ITEM_LEAF_STONE, .price = 800},
{.itemId = ITEM_SUN_STONE, .price = 800},
{0}
};


EWRAM_DATA static u16 sPermutation[MAX_SHOP_SIZE] = {0};
#define PX(arr, ix) (arr[sPermutation[ix]])

static void PopulateRandomShopItems(const struct ItemPrice *items, u16 count)
{
    u16 length = 0;
    u16 i, j;

    for (; items[length].itemId; length++);

    for (i = 0; i < count; i++) {
        while(1) {
            u16 index = Random() % length;
            for (j = 0; j < i; j++) {
                if (sPermutation[j] == index)
                    break;
            }
            if (j != i)
                continue;
            sPermutation[i] = index;
            break;
        }
    }

    for (i = 0; i < count; i++) {
        G_RANDOM_SHOP[i] = PX(items, i);
    }

    G_RANDOM_SHOP[count] = sItemPriceNone;
}


void CreateFixedShopMenu(u8 itempoolnum) {
    switch(itempoolnum) {
        case 0:
        default:
            CreatePokemartMenu(sBasicItems);
            break;
    }
}

void GenerateRandomShop(u8 itempoolnum) {
    switch(itempoolnum) {
        case 0:
            PopulateRandomShopItems(sDTutorialA1ItemPool, DEFAULT_SHOP_SIZE);
            break;
        case 1:
        default:
            PopulateRandomShopItems(sDEdenA1ItemPool, DEFAULT_SHOP_SIZE);
            break;
    }
}

void CreateRandomShopMenu() {
    CreatePokemartMenu(G_RANDOM_SHOP);
}
