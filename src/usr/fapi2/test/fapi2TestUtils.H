/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/usr/fapi2/test/fapi2TestUtils.H $                         */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2015,2018                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
///
/// @file fapi2TestUtils.H
///
/// @brief FAPI2 utility functions
///
/// Note that platform code must provide the implementation.
///

#ifndef FAPI2TESTUTILS_H_
#define FAPI2TESTUTILS_H_

#define EQ_PER_PROC          6
#define EX_PER_EQ            2
#define CORE_PER_EX          2
#define MCS_PER_PROC         4
#define MI_PER_PROC          4
#define MCA_PER_MCS          2
#define DMI_PER_MI           2
#define MCBIST_PER_PROC      2
#define MC_PER_PROC          2
#define MCS_PER_MCBIST       2
#define MI_PER_MC            2
#define PERV_PER_PROC        43
#define XBUS_PER_PROC        1
#define OBUS_PER_PROC        2

#define SIMULATED_GOOD_CORES 4

// non-core and non-cache chiplet ids
#define START_PERV_CHIPLET_NUM        0x01
// CAPI Unit(0,1 => 0x02, 0x04)
#define START_CAPP_CHIPLET_NUM        0x02
// OBUS BRICK ({0-2}, {9,11} => 0x09, 0xC)
#define START_OBUS_BRICK_CHIPLET_NUM  0x09
// XBUS (0, 1 => 0x6)
#define START_XBUS_CHIPLET_NUM        0x06
// MCBIST (0, 1 => 0x07, 0x08)
#define START_MCBIST_CHIPLET_NUM      0x07
// OBUS (0, 3 => 0x09, 0x0C)
#define START_OBUS_CHIPLET_NUM        0x09
// PEC (0, 1, 2 => 0x0D, 0x0E, 0x0F)
#define START_PEC_0_CHIPLET_NUM       0x0D
#define START_PEC_1_CHIPLET_NUM       0x0E
#define START_PEC_2_CHIPLET_NUM       0x0F

// All Cache Chiplets
#define START_EQ_CHIPLET_NUM      0x10

// All Core Chiplets
#define START_CORE_CHIPLET_NUM    0x20

#include <fapi2.H>

namespace fapi2
{

//Used by generateTargets to get a list of all platform target
// types that directly relate to fapi2 target types
enum{
    MY_EQ,
    MY_EX,
    MY_CORE,
    MY_MCS,
    MY_MCA,
    MY_MCBIST,
    MY_PEC,
    MY_PHB,
    MY_XBUS,
    MY_OBUS,
    MY_OBUS_BRICK,
    MY_PPE,
    MY_PERV,
    MY_CAPP,
    MY_SBE,
    MY_MC,
    MY_MI,
    MY_DMI,
    NUM_TARGETS
};

/**
 *  @brief Number of children of given type that applicable pervasive has
 */
enum PERVASIVE_CHILDREN {
    PERV_EQ_CHILDREN           = 1,
    PERV_CORE_CHILDREN         = 1,
    PERV_XBUS_NIMBUS_CHILDREN  = 2,
    PERV_XBUS_CUMULUS_CHILDREN = 3,
    PERV_OBUS_CHILDREN         = 1,
    PERV_CAPP_NIMBUS_CHILDREN  = 1,
    PERV_CAPP_CUMULUS_CHILDREN = 2,
    PERV_OBUS_BRICK_CHILDREN   = 3,
    PERV_MCBIST_CHILDREN       = 1,
    PERV_MCS_CHILDREN          = 2,
    PERV_MCA_CHILDREN          = 4,
    PERV_PEC_CHILDREN          = 1,
    PERV_PEC0_PHB_CHILDREN     = 1,
    PERV_PEC1_PHB_CHILDREN     = 2,
    PERV_PEC2_PHB_CHILDREN     = 3,
    PERV_MC_CHILDREN           = 1,
    PERV_MI_CHILDREN           = 2,
    PERV_DMI_CHILDREN          = 4,
};

/**
 *  @brief Unit ranges for pervasive function
 *
 *  @par Detailed Description:
 *      Maps pervasive target with chip unit X to one or more unit types.  For
 *      example, a pervasive chip unit of 18 maps to EQ type because
 *      EQ_LOW <= X <= EQ_HIGH .
 */
enum PERVASIVE_RANGE {
    EQ_LOW            = 16,
    EQ_HIGH           = 21,
    CORE_LOW          = 32,
    CORE_HIGH         = 55,
    XBUS_RANGE        = 6,
    OBUS_LOW          = 9,
    OBUS_HIGH         = 12,
    CAPP0_RANGE       = 2,
    CAPP1_RANGE       = 4,
    MC_LOW            = 7,
    MC_HIGH           = 8,
    PEC_LOW           = 13,
    PEC_MID           = 14,
    PEC_HIGH          = 15,
};

///
/// @brief Generates a list of platform targets of all differnt types.
///        This comes in handy when testing out fapi2 target interfaces
/// @param[in] i_pMasterProcChip Pointer to master proc chip
/// @param[out] o_targetList     List of platform targets that gets generated
///                              by this function
///
void generateTargets(TARGETING::Target* i_pMasterProcChip,
                                    TARGETING::Target* o_targetList[]);

/**
*  @brief Helper to get the parent pervasive of the given target
*
*  @tparam K Input target's FAPI2 type
*  @tparam V Platform target handle type
*
*  @param[in] i_pTarget Targeting target
*
*  @return Platform target handle giving the pervasive of the input target
*  @retval NULL No parent found
*  @retval !NULL Parent found, equal to the retval
 */
template< TargetType K, typename V = plat_target_handle_t >
inline V getPervasiveParent(V i_pTarget)
{
    Target<K,V> fapi2_target(i_pTarget);
    return static_cast<V>(
        fapi2_target.template getParent<TARGET_TYPE_PERV>());
}

/**
 * @brief Helper to determine if hw unit is valid for given
 *      proc type
 *
 * @param[in] i_procChip Proc chip to check type of
 * @param[in] i_hwType   Hw unit type to compare with proc
 *
 * @return True if hw unit is valid for proc type, false otherwise
 */
bool isHwValid(TARGETING::Target* i_procChip, uint8_t i_hwType);

} // End namespace fapi2
#endif
