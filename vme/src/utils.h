/*
 $Author: All $
 $RCSfile: utils.h,v $
 $Date: 2005/06/28 20:17:48 $
 $Revision: 2.7 $
 */
#pragma once

#include "constants.h"
#include "npc_data.h"
#include "obj_data.h"
#include "pc_data.h"
#include "room_data.h"
#include "weather.h"
#include "zone_type.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

// clang-format off
/* ..................................................................... */
// Forward declarations
inline ubit8 CHAR_SEX(const unit_data *ch);
inline ubit8 CHAR_LEVEL(const unit_data *ch);
inline bool CHAR_AWAKE(const unit_data *ch);
inline bool IS_ROOM(const unit_data *unit);
inline bool IS_OBJ(const unit_data *unit);
inline bool IS_NPC(const unit_data *unit);
inline bool IS_PC(const unit_data *unit);
inline bool IS_CHAR(const unit_data *unit);

#define PK_RELAXED 0
#define PK_STRICT 1

[[maybe_unused]] inline bool IS_BEGINNER(const unit_data *ch) { return CHAR_LEVEL(ch) <= START_LEVEL; }
inline bool IS_MORTAL(const unit_data *ch) { return CHAR_LEVEL(ch) < IMMORTAL_LEVEL; }
inline bool IS_IMMORTAL(const unit_data *ch) { return CHAR_LEVEL(ch) >= IMMORTAL_LEVEL; }
inline bool IS_GOD(const unit_data *ch) { return CHAR_LEVEL(ch) >= GOD_LEVEL; }
[[maybe_unused]] inline bool IS_CREATOR(const unit_data *ch) { return CHAR_LEVEL(ch) >= CREATOR_LEVEL; }
inline bool IS_OVERSEER(const unit_data *ch) { return CHAR_LEVEL(ch) >= OVERSEER_LEVEL; }
inline bool IS_ADMINISTRATOR(const unit_data *ch) { return CHAR_LEVEL(ch) >= ADMINISTRATOR_LEVEL; }
inline bool IS_ULTIMATE(const unit_data *ch) { return CHAR_LEVEL(ch) == ULTIMATE_LEVEL;}

/* ..................................................................... */

/*  Do NOT use these functions unless you know PRECISELY what you are doing!!!
 *  and only if you have to assign directly to them (as in db_utils.c)
 */

#ifdef MUD_DEBUG
    #define DEBUG_HISTORY
    #define UNIT_TYPE_DEBUG
#endif

inline char_data *UCHAR(const unit_data *u)
{
#ifdef UNIT_TYPE_DEBUG
    assert(u && IS_CHAR(u));
#endif
    return const_cast<char_data *>(dynamic_cast<const char_data *>(u));
}

inline npc_data *UNPC(const unit_data *u)
{
#ifdef UNIT_TYPE_DEBUG
    assert(u && IS_NPC(u));
#endif
    return const_cast<npc_data *>(dynamic_cast<const npc_data *>(u));
}

inline pc_data *UPC(const unit_data *u)
{
#ifdef UNIT_TYPE_DEBUG
    assert(u && IS_PC(u));
#endif
    return const_cast<pc_data *>(dynamic_cast<const pc_data *>(u));
}

inline obj_data *UOBJ(const unit_data *u)
{
#ifdef UNIT_TYPE_DEBUG
    assert(u && IS_OBJ(u));
#endif
    return const_cast<obj_data *>(dynamic_cast<const obj_data *>(u));
}

inline room_data *UROOM(const unit_data *u)
{
#ifdef UNIT_TYPE_DEBUG
    assert(u && IS_ROOM(u));
#endif
    return const_cast<room_data *>(dynamic_cast<const room_data *>(u));
}

inline sbit16 UNIT_ILLUM(unit_data *unit) { return unit->getTransparentLightOutput(); }

inline ubit8 UNIT_CHARS(const unit_data *unit) { return unit->getNumberOfCharactersInsideUnit(); }

inline unit_data *UNIT_CONTAINS(unit_data *unit) { return unit->getContainedUnits(); }
inline const unit_data *UNIT_CONTAINS(const unit_data *unit) { return unit->getContainedUnits(); }

inline unit_data *UNIT_IN(unit_data *unit) { return unit->getMyContainer(); }
inline unit_data *UNIT_IN(const unit_data *unit) { return const_cast<unit_data*>(unit)->getMyContainer(); }

inline unit_affected_type *UNIT_AFFECTED(unit_data *unit) { return unit->getUnitAffectedType(); }

inline const char *UNIT_NAME(const unit_data *unit) { return unit->getNames().Name(); }

inline const char *UNIT_KEY(unit_data *unit) { return unit->getKey(); }

inline ubit8 UNIT_OPEN_FLAGS(const unit_data *unit) { return unit->getOpenFlags(); }

inline ubit8 UNIT_OPEN_DIFF(unit_data *unit) { return unit->getOpenDifficulty(); }

inline ubit8 UNIT_TYPE(unit_data *unit) { return unit->getUnitType(); }
inline ubit8 UNIT_TYPE(const unit_data *unit) { return unit->getUnitType(); }

inline cNamelist &UNIT_NAMES(unit_data *unit) { return unit->getNames(); }

inline sbit16 UNIT_ALIGNMENT(unit_data *unit) { return unit->getAlignment(); }

inline sbit32 UNIT_HIT(unit_data *unit) { return unit->getCurrentHitpoints(); }

inline sbit32 UNIT_MAX_HIT(unit_data *unit) { return unit->getMaximumHitpoints(); }

inline ubit8 UNIT_MINV(const unit_data *unit) { return unit->getLevelOfWizardInvisibility(); }

inline const std::string &UNIT_TITLE(const unit_data *unit) { return unit->getTitle(); }

inline const std::string &UNIT_OUT_DESCR(const unit_data *unit) { return unit->getDescriptionOfOutside(); }

inline const std::string &UNIT_IN_DESCR(const unit_data *unit) { return unit->getDescriptionOfInside(); }

inline extra_list &UNIT_EXTRA(unit_data *unit) { return unit->getExtraList(); }
inline const extra_list &UNIT_EXTRA(const unit_data *unit) { return unit->getExtraList(); }
/* ..................................................................... */

inline bool IS_ROOM(const unit_data *unit) { return UNIT_TYPE(unit) == UNIT_ST_ROOM; }

inline bool IS_OBJ(const unit_data *unit) { return UNIT_TYPE(unit) == UNIT_ST_OBJ; }

inline bool IS_NPC(const unit_data *unit) { return UNIT_TYPE(unit) == UNIT_ST_NPC; }

inline bool IS_PC(const unit_data *unit) { return UNIT_TYPE(unit) == UNIT_ST_PC; }

inline bool IS_CHAR(const unit_data *unit)
{
    auto type = UNIT_TYPE(unit);
    return type == UNIT_ST_PC || type == UNIT_ST_NPC;
}

/* ............................FILE INDEX STUFF..................... */

inline const char *FI_ZONENAME(const file_index_type *fi) { return fi->getZone()->getName(); }

inline const char *FI_NAME(const file_index_type *fi) { return fi->getName(); }

/* ............................UNIT SUPERSTRUCTURES..................... */

inline bool UNIT_IS_TRANSPARENT(const unit_data *u)
{
    return !IS_SET(u->getUnitFlags(), UNIT_FL_BURIED) && IS_SET(u->getUnitFlags(), UNIT_FL_TRANS) && !IS_SET(UNIT_OPEN_FLAGS(u), EX_CLOSED);
}

inline zone_type *UNIT_FI_ZONE(unit_data *unit) { return (unit)->getFileIndex()->getZone(); }

inline const char *UNIT_FI_ZONENAME(const unit_data *unit) { return unit->getFileIndex() ? FI_ZONENAME(unit->getFileIndex()) : "NO-ZONE"; }

inline const char *UNIT_FI_NAME(const unit_data *unit) { return unit->getFileIndex() ? FI_NAME(unit->getFileIndex()) : "NO-NAME"; }

inline bool UNIT_WEAR(unit_data *unit, ubit32 part) { return IS_SET(unit->getManipulate(), part); }

inline bool UNIT_IS_OUTSIDE(const unit_data *unit) { return !IS_SET(UNIT_IN(unit)->getUnitFlags(), UNIT_FL_INDOORS); }

inline sbit8 UNIT_OUTSIDE_LIGHT(unit_data *unit) { return !IS_SET(unit->getUnitFlags(), UNIT_FL_INDOORS) ? g_time_light[g_sunlight] : 0; }

[[maybe_unused]] inline sbit16 UNIT_IS_DARK(unit_data *unit) { return unit->getNumberOfActiveLightSources() + UNIT_OUTSIDE_LIGHT(unit) + (UNIT_IN(unit) ? UNIT_IN(unit)->getNumberOfActiveLightSources() : 0) < 0; }

inline sbit16 UNIT_IS_LIGHT(unit_data *unit) { return unit->getNumberOfActiveLightSources() + UNIT_OUTSIDE_LIGHT(unit) + (UNIT_IN(unit) ? UNIT_IN(unit)->getNumberOfActiveLightSources() : 0) >= 0; }

inline ubit8 UNIT_SEX(const unit_data *unit) { return IS_CHAR(unit) ? CHAR_SEX(unit) : SEX_NEUTRAL; }

inline bool UNIT_IS_GOOD(unit_data *ch) { return UNIT_ALIGNMENT(ch) >= 350; }
inline bool UNIT_IS_EVIL(unit_data *ch) { return UNIT_ALIGNMENT(ch) <= -350; }
inline bool UNIT_IS_NEUTRAL(unit_data *ch) { return !UNIT_IS_GOOD(ch) && !UNIT_IS_EVIL(ch); }

inline sbit32 UNIT_CONTAINING_W(unit_data *u) { return u->getWeight() - u->getBaseWeight(); }

/* ..................................................................... */

inline ubit8 ROOM_RESISTANCE(unit_data *room) { return UROOM(room)->getRoomMagicalResistance(); }

inline ubit8 ROOM_LANDSCAPE(const unit_data *unit) { return UROOM(unit)->getLandscapeTerrain(); }

inline ubit8 ROOM_FLAGS(const unit_data *unit) { return UROOM(unit)->getRoomFlags(); }

inline room_direction_data *ROOM_EXIT(unit_data *unit, size_t exit) { return UROOM(unit)->getRoomDirectionDataForExit(exit); }

inline int ROOM_NUM(const unit_data *unit) { return UROOM(unit)->getRoomNumber(); }

inline int ROOM_SC(const unit_data *unit) { return UROOM(unit)->getStrongComponent(); }

#ifndef MPLEX_COMPILE
    inline std::vector<room_data::vertex_descriptor> &ROOM_PATH(unit_data *unit) { return UROOM(unit)->getPath(); }
    inline std::vector<room_data::vertex_descriptor> &ROOM_DISTANCE(unit_data *unit) { return UROOM(unit)->getDistance();}
#endif

/* ..................................................................... */

inline ubit8 OBJ_RESISTANCE(unit_data *obj) { return UOBJ(obj)->getMagicResistance(); }

inline sbit32 OBJ_VALUE(const unit_data *unit, size_t index) { return UOBJ(unit)->getValueAtIndex(index); }

inline ubit32 OBJ_PRICE(const unit_data *unit) { return UOBJ(unit)->getPriceInGP(); }

inline ubit32 OBJ_PRICE_DAY(unit_data *unit) { return UOBJ(unit)->getPricePerDay(); }

inline ubit8 OBJ_TYPE(const unit_data *unit) { return UOBJ(unit)->getObjectItemType(); }

inline ubit8 OBJ_EQP_POS(unit_data *unit) { return UOBJ(unit)->getEquipmentPosition(); }

inline ubit8 OBJ_FLAGS(unit_data *obj) { return UOBJ(obj)->getObjectFlags(); }

/* ...........................OBJECT SUPERSTRUCTURES..................... */

inline bool UNIT_IS_EQUIPPED(unit_data *obj) { return IS_OBJ(obj) && OBJ_EQP_POS(obj); }

/* ..................................................................... */

inline const descriptor_data *CHAR_DESCRIPTOR(const unit_data *ch) { return UCHAR(ch)->getDescriptor(); }

inline descriptor_data *CHAR_DESCRIPTOR(unit_data *ch) { return UCHAR(ch)->getDescriptor(); }

inline sbit16 CHAR_OFFENSIVE(const unit_data *unit) { return UCHAR(unit)->getOffensiveBonus(); }

inline sbit16 CHAR_DEFENSIVE(const unit_data *unit) { return UCHAR(unit)->getDefensiveBonus(); }

inline ubit32 CHAR_FLAGS(const unit_data *unit) { return UCHAR(unit)->getCharacterFlags(); }

inline ubit8 CHAR_SEX(const unit_data *ch) { return UCHAR(ch)->getSex(); }

inline unit_data *CHAR_LAST_ROOM(unit_data *unit) { return UCHAR(unit)->getLastLocation(); }

inline const char *CHAR_LAST_ATTACKER(const unit_data *unit) { return UCHAR(unit)->getLastAttacker(); }

inline ubit8 CHAR_LAST_ATTACKER_TYPE(const unit_data *unit) { return UCHAR(unit)->getLastAttackerType(); }

inline ubit8 CHAR_POS(const unit_data *ch) { return UCHAR(ch)->getPosition(); }

inline ubit8 CHAR_LEVEL(const unit_data *ch) { return UCHAR(ch)->getLevel(); }

inline ubit16 CHAR_RACE(const unit_data *ch) { return UCHAR(ch)->getRace(); }

inline sbit16 CHAR_ABILITY(const unit_data *ch, size_t index) { return UCHAR(ch)->getAbilityAtIndex(index); }

inline sbit16 CHAR_STR(const unit_data *ch) { return UCHAR(ch)->getSTR(); }

inline sbit16 CHAR_DEX(const unit_data *ch) { return UCHAR(ch)->getDEX(); }

inline sbit16 CHAR_CON(const unit_data *ch) { return UCHAR(ch)->getCON(); }

inline sbit16 CHAR_CHA(const unit_data *ch) { return UCHAR(ch)->getCHA(); }

inline sbit16 CHAR_BRA(const unit_data *ch) { return UCHAR(ch)->getBRA(); }

inline sbit16 CHAR_MAG(const unit_data *ch) { return UCHAR(ch)->getMAG(); }

inline sbit16 CHAR_DIV(const unit_data *ch) { return UCHAR(ch)->getDIV(); }

inline sbit16 CHAR_HPP(const unit_data *ch) { return UCHAR(ch)->getHPP(); }

inline sbit16 CHAR_ENDURANCE(const unit_data *ch) { return UCHAR(ch)->getEndurance(); }

inline sbit16 CHAR_MANA(const unit_data *ch) { return UCHAR(ch)->getMana(); }

/* NOT to be used unless by db.... */
[[maybe_unused]] inline const char *CHAR_MONEY(const unit_data *ch) { return UCHAR(ch)->getMoney(); }

inline char *CHAR_MONEY(unit_data *ch) { return UCHAR(ch)->getMoney(); }

inline sbit32 CHAR_EXP(const unit_data *ch) { return UCHAR(ch)->getPlayerExperience(); }

inline ubit8 CHAR_ATTACK_TYPE(const unit_data *ch) { return UCHAR(ch)->getAttackType(); }

inline ubit8 CHAR_NATURAL_ARMOUR(const unit_data *ch) { return UCHAR(ch)->getNaturalArmor(); }

inline sbit16 CHAR_SPEED(const unit_data *ch) { return UCHAR(ch)->getSpeed(); }

inline cCombat *CHAR_COMBAT(unit_data *ch) { return UCHAR(ch)->getCombat(); }

inline unit_data *CHAR_FIGHTING(unit_data *ch) { return UCHAR(ch)->getCombat() ? CHAR_COMBAT(ch)->Melee() : nullptr; }

inline unit_data *CHAR_MASTER(unit_data *ch) { return UCHAR(ch)->getMaster(); }

inline char_follow_type *CHAR_FOLLOWERS(const unit_data *ch) { return UCHAR(ch)->getFollowers(); }
/* ...........................CHAR SUPERSTRUCTURES....................... */

inline bool CHAR_IS_READY(unit_data *ch) { return CHAR_AWAKE(ch) && (CHAR_POS(ch) != POSITION_FIGHTING); }

inline unit_data *CHAR_IS_SNOOPING(unit_data *ch) { return CHAR_DESCRIPTOR(ch) ? CHAR_DESCRIPTOR(ch)->getSnoopData().getSnooping() : nullptr; }

inline unit_data *CHAR_IS_SNOOPED(unit_data *ch) { return CHAR_DESCRIPTOR(ch) ? CHAR_DESCRIPTOR(ch)->getSnoopData().getSnoopBy() : nullptr; }

inline unit_data *CHAR_IS_SWITCHED(unit_data *ch) { return CHAR_DESCRIPTOR(ch) ? CHAR_DESCRIPTOR(ch)->getOriginalCharacter() : nullptr; }

[[maybe_unused]] inline unit_data *CHAR_SNOOPING(unit_data *ch) { return CHAR_IS_SNOOPING(ch) ? (CHAR_DESCRIPTOR(ch)->getSnoopData().getSnooping()) : (ch); }

[[maybe_unused]] inline unit_data *CHAR_SNOOPED(unit_data *ch) { return CHAR_IS_SNOOPED(ch) ? (CHAR_DESCRIPTOR(ch)->getSnoopData().getSnoopBy()) : (ch); }

inline unit_data *CHAR_ORIGINAL(unit_data *ch)
{
    return CHAR_IS_SWITCHED(ch) ? CHAR_DESCRIPTOR(ch)->getOriginalCharacter() : ch;
}

inline bool CHAR_AWAKE(const unit_data *ch) { return CHAR_POS(ch) > POSITION_SLEEPING; }

inline bool CHAR_HAS_FLAG(const unit_data *ch, ubit32 flags) { return IS_SET(CHAR_FLAGS(ch), (flags)); }

[[maybe_unused]] inline room_direction_data *CHAR_ROOM_EXIT(unit_data *ch, size_t door) { return IS_ROOM(UNIT_IN(ch)) ? ROOM_EXIT(UNIT_IN(ch), door) : nullptr; }

inline bool CHAR_VISION(const unit_data *ch) { return !CHAR_HAS_FLAG(ch, CHAR_BLIND); }

inline bool CHAR_CAN_SEE(const unit_data *ch, const unit_data *unit)
{
    // Made the decision that you can always see what you are inside, so you can e.g. knock a coffin you've been buried in
    return !IS_CHAR(ch) ||
           (CHAR_VISION(ch) && (!IS_SET(unit->getUnitFlags(), UNIT_FL_BURIED) || UNIT_IN(ch) == unit) && CHAR_LEVEL(ch) >= UNIT_MINV(unit) &&
            (CHAR_LEVEL(ch) >= CREATOR_LEVEL ||
             (UNIT_IS_LIGHT(UNIT_IN(ch)) && (!IS_SET(unit->getUnitFlags(), UNIT_FL_INVISIBLE) || CHAR_HAS_FLAG(ch, CHAR_DETECT_INVISIBLE)))));
}

inline bool CHAR_CAN_SEE(unit_data *ch, unit_data *unit)
{
    return CHAR_CAN_SEE(const_cast<const unit_data *>(ch), const_cast<const unit_data *>(unit));
}

[[maybe_unused]] inline bool CHAR_CAN_GO(unit_data *ch, size_t door) { return ROOM_EXIT(UNIT_IN(ch), door) && ROOM_EXIT(UNIT_IN(ch), door)->getToRoom() && !IS_SET(ROOM_EXIT(UNIT_IN(ch), door)->getDoorFlags(), EX_CLOSED); }

/* ..................................................................... */

inline ubit8 PC_ACCESS_LEVEL(unit_data *pc) { return UPC(pc)->getAccessLevel(); }

inline ubit16 PC_CRACK_ATTEMPTS(unit_data *pc) { return UPC(pc)->getNumberOfCrackAttempts(); }

inline terminal_setup_type &PC_SETUP(unit_data *pc) { return UPC(pc)->getTerminalSetupType(); }

inline ubit16 PC_LIFESPAN(unit_data *pc) { return UPC(pc)->getLifespan(); }

inline pc_account_data &PC_ACCOUNT(unit_data *pc) { return UPC(pc)->getPCAccountData(); }

inline pc_account_data &PC_ACCOUNT(const unit_data *pc) { return UPC(pc)->getPCAccountData(); }

inline ubit16 PC_VIRTUAL_LEVEL(unit_data *pc) { return UPC(pc)->getVirtualPlayerLevel(); }

inline extra_list &PC_INFO(unit_data *pc) { return UPC(pc)->getAdministrationInformation(); }

inline ubit8 PC_SETUP_ECHO(unit_data *pc) { return UPC(pc)->getTerminalSetupType().echo; }

inline ubit8 PC_SETUP_REDRAW(unit_data *pc) { return UPC(pc)->getTerminalSetupType().redraw; }

inline ubit8 PC_SETUP_WIDTH(unit_data *pc) { return UPC(pc)->getTerminalSetupType().width; }

inline ubit8 PC_SETUP_HEIGHT(unit_data *pc) { return UPC(pc)->getTerminalSetupType().height; }

inline ubit8 PC_SETUP_TELNET(unit_data *pc) { return UPC(pc)->getTerminalSetupType().telnet; }

inline ubit8 PC_SETUP_EMULATION(unit_data *pc) { return UPC(pc)->getTerminalSetupType().emulation; }

inline ubit8 PC_SETUP_COLOUR(unit_data *pc) { return UPC(pc)->getTerminalSetupType().colour_convert; }

inline const char *PC_GUILD(unit_data *pc) { return UPC(pc)->getGuild(); }

[[maybe_unused]] inline const char *PC_PROMPTSTR(unit_data *pc) { return UPC(pc)->getPromptString(); }

inline sbit8 PC_PROFESSION(unit_data *pc) { return UPC(pc)->getProfession(); }

inline extra_list &PC_QUEST(unit_data *pc) { return UPC(pc)->getQuestInformation(); }

inline sbit8 PC_COND(unit_data *ch, size_t i) { return UPC(ch)->getConditionAtIndex(i); }

inline sbit32 PC_ABILITY_POINTS(unit_data *ch) { return UPC(ch)->getAbilityPoints(); }

inline sbit32 PC_SKILL_POINTS(unit_data *ch) { return UPC(ch)->getSkillPoints(); }

inline ubit8 PC_ABI_LVL(unit_data *ch, size_t index) { return UPC(ch)->getAbilityLevelAtIndex(index); }

inline sbit16 PC_SKI_SKILL(unit_data *ch, size_t index) { return UPC(ch)->getSkillAtIndex(index); }

inline ubit8 PC_SKI_LVL(unit_data *ch, size_t index) { return UPC(ch)->getSpellSkillAtIndex(index); }

inline ubit8 PC_WPN_LVL(unit_data *ch, size_t index) { return UPC(ch)->getWeaponSkillLevelAtIndex(index); }

inline sbit16 PC_WPN_SKILL(unit_data *ch, size_t index) { return UPC(ch)->getWeaponSkillAtIndex(index); }

inline ubit8 PC_SPL_LVL(unit_data *ch, size_t index) { return UPC(ch)->getSpellLevelAtIndex(index); }

inline sbit16 PC_SPL_SKILL(unit_data *ch, size_t index) { return UPC(ch)->getSpellSkillAtIndex(index); }

inline ubit16 PC_CRIMES(unit_data *unit) { return UPC(unit)->getNumberOfCrimesCommitted(); }

inline const char *PC_PWD(unit_data *unit) { return UPC(unit)->getPassword(); }

inline const char *PC_FILENAME(unit_data *unit) { return UPC(unit)->getFilename(); }

inline sbit32 PC_ID(unit_data *unit) { return UPC(unit)->getPlayerUID(); }

inline const char *PC_BANK(const unit_data *unit) { return UPC(unit)->getBank(); }

inline ubit16 PC_FLAGS(unit_data *unit) { return UPC(unit)->getAllPCFlags(); }

inline pc_time_data &PC_TIME(unit_data *unit) { return UPC(unit)->getPCTimeInformation(); }

inline const char *PC_HOME(unit_data *ch) { return UPC(ch)->getHometown(); }
/* .................... PC SUPER STRUCTURE ............................. */

inline bool PC_IMMORTAL(unit_data *ch) { return IS_PC(ch) && CHAR_LEVEL(ch) >= 200; }

[[maybe_unused]] inline bool PC_MORTAL(unit_data *ch) { return IS_PC(ch) && CHAR_LEVEL(ch) < 200; }

inline bool PC_IS_UNSAVED(unit_data *ch) { return PC_TIME(ch).getTotalTimePlayedInSeconds() == 0; }

/* ..................................................................... */

inline sbit16 NPC_WPN_SKILL(unit_data *ch, size_t index)
{
    return UNPC(ch)->getWeaponSkillAtIndex(index);
}

inline sbit16 NPC_SPL_SKILL(unit_data *ch, size_t index)
{
    return UNPC(ch)->getSpellSkillAtIndex(index);
}

inline ubit8 NPC_DEFAULT(unit_data *unit)
{
    return UNPC(unit)->getDefaultPosition();
}

inline ubit8 NPC_FLAGS(unit_data *unit)
{
    return UNPC(unit)->getAllNPCFlags();
}

/* ..................................................................... */
inline const char *UNIT_TITLE_STRING(unit_data *unit) { return UNIT_TITLE(unit).c_str(); }

inline const char *UNIT_OUT_DESCR_STRING(unit_data *unit) { return UNIT_OUT_DESCR(unit).c_str(); }

inline const char *UNIT_IN_DESCR_STRING(unit_data *unit) { return UNIT_IN_DESCR(unit).c_str(); }

inline const char *TITLENAME(unit_data *unit) { return IS_PC(unit) ? UNIT_NAME(unit) : UNIT_TITLE_STRING(unit); }

inline const char *SOMETON(const unit_data *unit) { return UNIT_SEX(unit) == SEX_NEUTRAL ? "something" : "someone"; }

/* Title, Name or Someone/Something */
inline const char *UNIT_SEE_TITLE(unit_data *ch, unit_data *unit) { return CHAR_CAN_SEE(ch, unit) ? TITLENAME(unit) : SOMETON(unit); }

inline const char *UNIT_SEE_NAME(const unit_data *ch, const unit_data *unit) { return CHAR_CAN_SEE(ch, unit) ? UNIT_NAME(unit) : SOMETON(unit); }
/* ..................................................................... */

/* Invis people aren't supposed to have sex... /gnort */

inline const char *B_HSHR(const unit_data *ch) { return UNIT_SEX(ch) == SEX_NEUTRAL ? "its" : (CHAR_SEX(ch) == SEX_MALE) ? "his" : "her"; }

inline const char *HSHR(const unit_data *to, const unit_data *ch) { return CHAR_CAN_SEE((to), (ch)) ? B_HSHR(ch) : "their"; }

inline const char *B_HESH(const unit_data *ch) { return UNIT_SEX(ch) == SEX_NEUTRAL ? "it" : (CHAR_SEX(ch) == SEX_MALE) ? "he" : "she"; }

inline const char *HESH(const unit_data *to, const unit_data *ch) { return CHAR_CAN_SEE(to, ch) ? B_HESH(ch) : "they"; }

inline const char *B_HMHR(const unit_data *ch) { return UNIT_SEX(ch) == SEX_NEUTRAL ? "it" : CHAR_SEX(ch) == SEX_MALE ? "him" : "her"; }

inline const char *HMHR(const unit_data *to, const unit_data *ch) { return CHAR_CAN_SEE(to, ch) ? B_HMHR(ch) : "them"; }

inline const char *UNIT_ANA(unit_data *unit) { return ANA(*UNIT_NAME(unit)); }

// clang-format on
