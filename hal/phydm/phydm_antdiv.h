/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *                                        
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef	__PHYDMANTDIV_H__
#define    __PHYDMANTDIV_H__

/*#define ANTDIV_VERSION	"2.0"  //2014.11.04*/
/*#define ANTDIV_VERSION	"2.1"  //2015.01.13  Dino*/
/*#define ANTDIV_VERSION	"2.2"  2015.01.16  Dino*/
/*#define ANTDIV_VERSION	"3.1"  2015.07.29  YuChen, remove 92c 92d 8723a*/
/*#define ANTDIV_VERSION	"3.2"  2015.08.11  Stanley, disable antenna diversity when BT is enable for 8723B*/
/*#define ANTDIV_VERSION	"3.3"  2015.08.12  Stanley. 8723B does not need to check the antenna is control by BT, 
							because antenna diversity only works when BT is disable or radio off*/
#define ANTDIV_VERSION	"3.4"  /*2015.08.28  Dino  1.Add 8821A Smart Antenna 2. Add 8188F SW S0S1 Antenna Diversity*/

//1 ============================================================
//1  Definition 
//1 ============================================================

#define	MAIN_ANT	1
#define	AUX_ANT	2

#define ANT1_2G 0 // = ANT2_5G
#define ANT2_2G 1 // = ANT1_5G
/*smart antenna*/
#define SUPPORT_RF_PATH_NUM 4
#define SUPPORT_BEAM_PATTERN_NUM 4


//Antenna Diversty Control Type
#define	ODM_AUTO_ANT		0
#define	ODM_FIX_MAIN_ANT	1
#define	ODM_FIX_AUX_ANT	2

#define ODM_N_ANTDIV_SUPPORT		(ODM_RTL8192E|ODM_RTL8723B|ODM_RTL8188F)
#define ODM_AC_ANTDIV_SUPPORT	(ODM_RTL8821|ODM_RTL8881A|ODM_RTL8812)
#define ODM_ANTDIV_SUPPORT		(ODM_N_ANTDIV_SUPPORT|ODM_AC_ANTDIV_SUPPORT)
#define ODM_SMART_ANT_SUPPORT	(ODM_RTL8188E|ODM_RTL8192E)
#define ODM_HL_SMART_ANT_TYPE1_SUPPORT		(ODM_RTL8821)

#define ODM_ANTDIV_2G_SUPPORT_IC			(ODM_RTL8188E|ODM_RTL8192E|ODM_RTL8723B|ODM_RTL8881A|ODM_RTL8188F)
#define ODM_ANTDIV_5G_SUPPORT_IC			(ODM_RTL8821|ODM_RTL8881A|ODM_RTL8812)

#define ODM_EVM_ENHANCE_ANTDIV_SUPPORT_IC	(ODM_RTL8192E)

#define ODM_ANTDIV_2G	BIT0
#define ODM_ANTDIV_5G	BIT1

#define ANTDIV_ON	1
#define ANTDIV_OFF	0

#define FAT_ON	1
#define FAT_OFF	0

#define TX_BY_DESC	1
#define TX_BY_REG	0

#define RSSI_METHOD		0
#define EVM_METHOD		1
#define CRC32_METHOD	2

#define INIT_ANTDIV_TIMMER		0
#define CANCEL_ANTDIV_TIMMER	1
#define RELEASE_ANTDIV_TIMMER	2

#define CRC32_FAIL	1
#define CRC32_OK	0

#define Evm_RSSI_TH_High	25
#define Evm_RSSI_TH_Low	20

#define NORMAL_STATE_MIAN	1
#define NORMAL_STATE_AUX	2
#define TRAINING_STATE		3

#define FORCE_RSSI_DIFF 10

#define CSI_ON	1
#define CSI_OFF	0

#define DIVON_CSIOFF 1
#define DIVOFF_CSION 2

#define BDC_DIV_TRAIN_STATE	0
#define BDC_BFer_TRAIN_STATE	1
#define BDC_DECISION_STATE		2
#define BDC_BF_HOLD_STATE		3
#define BDC_DIV_HOLD_STATE		4

#define BDC_MODE_1 1
#define BDC_MODE_2 2
#define BDC_MODE_3 3
#define BDC_MODE_4 4
#define BDC_MODE_NULL 0xff

/*SW S0S1 antenna diversity*/
#define SWAW_STEP_INIT			0xff
#define SWAW_STEP_PEEK		0
#define SWAW_STEP_DETERMINE	1

#define RSSI_CHECK_RESET_PERIOD	10
#define RSSI_CHECK_THRESHOLD		50

/*Hong Lin Smart antenna*/
#define HL_SMTANT_2WIRE_DATA_LEN 24

//1 ============================================================
//1  structure
//1 ============================================================


typedef struct _SW_Antenna_Switch_
{
	u1Byte		Double_chk_flag;	/*If current antenna RSSI > "RSSI_CHECK_THRESHOLD", than check this antenna again*/
	u1Byte		try_flag;
	s4Byte		PreRSSI;
	u1Byte		CurAntenna;
	u1Byte		PreAntenna;
	u1Byte		RSSI_Trying;
	u1Byte 		reset_idx;
	u1Byte		Train_time;
	u1Byte		Train_time_flag; /*base on RSSI difference between two antennas*/
	RT_TIMER	phydm_SwAntennaSwitchTimer;
	u4Byte		PktCnt_SWAntDivByCtrlFrame;
	BOOLEAN		bSWAntDivByCtrlFrame;
	
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)	
	#if USE_WORKITEM
	RT_WORK_ITEM	phydm_SwAntennaSwitchWorkitem;	
	#endif
	#endif	

	/* AntDect (Before link Antenna Switch check) need to be moved*/
	u2Byte		Single_Ant_Counter;
	u2Byte		Dual_Ant_Counter;
	u2Byte		Aux_FailDetec_Counter;
	u2Byte		Retry_Counter;	
	u1Byte		SWAS_NoLink_State;
	u4Byte		SWAS_NoLink_BK_Reg948;
	BOOLEAN		ANTA_ON;	/*To indicate Ant A is or not*/
	BOOLEAN		ANTB_ON;	/*To indicate Ant B is on or not*/
	BOOLEAN		Pre_Aux_FailDetec;
	BOOLEAN		RSSI_AntDect_bResult;	
	u1Byte		Ant5G;
	u1Byte		Ant2G;

	
}SWAT_T, *pSWAT_T;


#if (DM_ODM_SUPPORT_TYPE & (ODM_AP))
#endif

#ifdef CONFIG_HL_SMART_ANTENNA_TYPE1
typedef struct _SMART_ANTENNA_TRAINNING_ {
	u4Byte	latch_time;
	BOOLEAN	pkt_skip_statistic_en;
	u4Byte	fix_beam_pattern_en;
	u4Byte	fix_training_num_en;
	u4Byte	fix_beam_pattern_codeword;
	u4Byte	update_beam_codeword;
	u4Byte	ant_num; /*number of smart beam antenna*/
	u4Byte	beam_patten_num_each_ant;/*number of  beam can be switched in each antenna*/
	u4Byte	data_codeword_bit_num;
	u4Byte	per_beam_training_pkt_num;
	u1Byte	decision_holding_period;
	u4Byte	pkt_counter;
	u4Byte	fast_training_beam_num;
	u4Byte	pre_fast_training_beam_num;
	u4Byte	pkt_rssi_pre[SUPPORT_RF_PATH_NUM][SUPPORT_BEAM_PATTERN_NUM];
	u4Byte	pkt_rssi_sum[8][SUPPORT_BEAM_PATTERN_NUM];
	u4Byte	pkt_rssi_cnt[8][SUPPORT_BEAM_PATTERN_NUM];
	u4Byte	rx_idle_beam[SUPPORT_RF_PATH_NUM];
	u4Byte	pre_codeword;
	BOOLEAN	force_update_beam_en;

	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)	
	RT_WORK_ITEM	hl_smart_antenna_workitem;
	RT_WORK_ITEM	hl_smart_antenna_decision_workitem;	
	#endif

} SAT_T, *pSAT_T;
#endif

typedef struct _FAST_ANTENNA_TRAINNING_
{
	u1Byte	Bssid[6];
	u1Byte	antsel_rx_keep_0;
	u1Byte	antsel_rx_keep_1;
	u1Byte	antsel_rx_keep_2;
	u1Byte	antsel_rx_keep_3;
	u4Byte	antSumRSSI[7];
	u4Byte	antRSSIcnt[7];
	u4Byte	antAveRSSI[7];
	u1Byte	FAT_State;
	u4Byte	TrainIdx;
	u1Byte	antsel_a[ODM_ASSOCIATE_ENTRY_NUM];
	u1Byte	antsel_b[ODM_ASSOCIATE_ENTRY_NUM];
	u1Byte	antsel_c[ODM_ASSOCIATE_ENTRY_NUM];
	u4Byte	MainAnt_Sum[ODM_ASSOCIATE_ENTRY_NUM];
	u4Byte	AuxAnt_Sum[ODM_ASSOCIATE_ENTRY_NUM];
	u4Byte	MainAnt_Cnt[ODM_ASSOCIATE_ENTRY_NUM];
	u4Byte	AuxAnt_Cnt[ODM_ASSOCIATE_ENTRY_NUM];
	u1Byte	RxIdleAnt;
	u1Byte	AntDiv_OnOff;
	BOOLEAN	bBecomeLinked;
	u4Byte	MinMaxRSSI;
	u1Byte	idx_AntDiv_counter_2G;
	u1Byte	idx_AntDiv_counter_5G;
	u1Byte	AntDiv_2G_5G;
	u4Byte    CCK_counter_main;
	u4Byte    CCK_counter_aux;	
	u4Byte    OFDM_counter_main;
	u4Byte    OFDM_counter_aux;

	#ifdef ODM_EVM_ENHANCE_ANTDIV
	u4Byte	MainAntEVM_Sum[ODM_ASSOCIATE_ENTRY_NUM];
	u4Byte	AuxAntEVM_Sum[ODM_ASSOCIATE_ENTRY_NUM];
	u4Byte	MainAntEVM_Cnt[ODM_ASSOCIATE_ENTRY_NUM];
	u4Byte	AuxAntEVM_Cnt[ODM_ASSOCIATE_ENTRY_NUM];
	BOOLEAN	EVM_method_enable;
	u1Byte	TargetAnt_EVM;
	u1Byte	TargetAnt_CRC32;
	u1Byte	TargetAnt_enhance;
	u1Byte	pre_TargetAnt_enhance;
	u2Byte	Main_MPDU_OK_cnt;
	u2Byte	Aux_MPDU_OK_cnt;	

	u4Byte	CRC32_Ok_Cnt;
	u4Byte	CRC32_Fail_Cnt;
	u4Byte	MainCRC32_Ok_Cnt;
	u4Byte	AuxCRC32_Ok_Cnt;
	u4Byte	MainCRC32_Fail_Cnt;
	u4Byte	AuxCRC32_Fail_Cnt;
	#endif	
	#if (DM_ODM_SUPPORT_TYPE & (ODM_WIN|ODM_CE))
	u4Byte    CCK_CtrlFrame_Cnt_main;
	u4Byte    CCK_CtrlFrame_Cnt_aux;
	u4Byte    OFDM_CtrlFrame_Cnt_main;
	u4Byte    OFDM_CtrlFrame_Cnt_aux;
	u4Byte	MainAnt_CtrlFrame_Sum;
	u4Byte	AuxAnt_CtrlFrame_Sum;
	u4Byte	MainAnt_CtrlFrame_Cnt;
	u4Byte	AuxAnt_CtrlFrame_Cnt;
	#endif
	BOOLEAN	fix_ant_bfee;
	BOOLEAN	enable_ctrl_frame_antdiv;
	BOOLEAN	use_ctrl_frame_antdiv;
	u1Byte	hw_antsw_occur;
}FAT_T,*pFAT_T;


//1 ============================================================
//1  enumeration
//1 ============================================================



typedef enum _FAT_STATE /*Fast antenna training*/
{
	FAT_BEFORE_LINK_STATE	= 0,
	FAT_PREPARE_STATE			= 1,
	FAT_TRAINING_STATE		= 2,
	FAT_DECISION_STATE		= 3
}FAT_STATE_E, *PFAT_STATE_E;

typedef enum _ANT_DIV_TYPE
{
	CG_TRX_HW_ANTDIV			= 0x01,
	CGCS_RX_HW_ANTDIV		= 0x02,
	CG_TRX_SMART_ANTDIV		= 0x03,
	S0S1_SW_ANTDIV			= 0x04, /*8723B intrnal switch S0 S1*/
	HL_SW_SMART_ANT_TYPE1	= 0x10 /*Hong-Lin Smart antenna use for 8821AE which is a 2 Ant. entitys, and each Ant. is equipped with 4 antenna patterns*/
}ANT_DIV_TYPE_E, *PANT_DIV_TYPE_E;


//1 ============================================================
//1  function prototype
//1 ============================================================


VOID
ODM_StopAntennaSwitchDm(
	IN	PVOID	pDM_VOID
	);
VOID
ODM_SetAntConfig(
	IN	PVOID	pDM_VOID,
	IN	u1Byte		antSetting	// 0=A, 1=B, 2=C, ....
	);


#define SwAntDivRestAfterLink	ODM_SwAntDivRestAfterLink

VOID ODM_SwAntDivRestAfterLink(	
	IN	PVOID	pDM_VOID
	);

VOID
ODM_AntDivReset(
	IN		PVOID		pDM_VOID
);

VOID
odm_AntennaDiversityInit(
	IN		PVOID		pDM_VOID
);

VOID
odm_AntennaDiversity(
	IN		PVOID		pDM_VOID
);


#endif /*#ifndef	__ODMANTDIV_H__*/
