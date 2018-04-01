;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module main
	.optsdcc -mmcs51 --model-large
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _SendMessage
	.globl _process_type
	.globl _process_time
	.globl _process_rx
	.globl _RF24readMessage
	.globl _RF24write
	.globl _flush_fifo_irq
	.globl _BuildApollonMessage
	.globl _BuildMessage
	.globl _isrINTERRUPT_VECTOR_T0
	.globl _adc_configure
	.globl _pwr_clk_mgmt_clklf_configure
	.globl _timer0_configure
	.globl _gpio_pin_configure
	.globl _rf_spi_execute_command
	.globl _rf_irq_clear_all
	.globl _rf_spi_configure_enable
	.globl _rf_read_rx_payload_width
	.globl _rf_read_rx_payload
	.globl _rf_set_rx_addr
	.globl _rf_set_tx_addr
	.globl _rf_write_register
	.globl _rf_power_up_param
	.globl _delay_us
	.globl _FSR_SB_ENDBG
	.globl _FSR_SB_STP
	.globl _FSR_SB_WEN
	.globl _FSR_SB_RDYN
	.globl _FSR_SB_INFEN
	.globl _FSR_SB_RDISMB
	.globl _RFCON_SB_RFCKEN
	.globl _RFCON_SB_RFCSN
	.globl _RFCON_SB_RFCE
	.globl _ADCON_SB_BD
	.globl _PSW_SB_P
	.globl _PSW_SB_F1
	.globl _PSW_SB_OV
	.globl _PSW_SB_RS0
	.globl _PSW_SB_RS1
	.globl _PSW_SB_F0
	.globl _PSW_SB_AC
	.globl _PSW_SB_CY
	.globl _T2CON_SB_T2PS
	.globl _T2CON_SB_I3FR
	.globl _T2CON_SB_I2FR
	.globl _T2CON_SB_T2R1
	.globl _T2CON_SB_T2R0
	.globl _T2CON_SB_T2CM
	.globl _T2CON_SB_T2I1
	.globl _T2CON_SB_T2I0
	.globl _IRCON_SB_EXF2
	.globl _IRCON_SB_TF2
	.globl _IRCON_SB_TICK
	.globl _IRCON_SB_MISCIRQ
	.globl _IRCON_SB_WUOPIRQ
	.globl _IRCON_SB_SPI_2WIRE
	.globl _IRCON_SB_RFIRQ
	.globl _IRCON_SB_RFRDY
	.globl _IEN1_SB_T2EXTRLD
	.globl _IEN1_SB_TICK
	.globl _IEN1_SB_MISCIRQ
	.globl _IEN1_SB_WUOPIRQ
	.globl _IEN1_SB_SPI_2WIRE
	.globl _IEN1_SB_RFIRQ
	.globl _IEN1_SB_RFRDY
	.globl _P3_SB_D7
	.globl _P3_SB_D6
	.globl _P3_SB_D5
	.globl _P3_SB_D4
	.globl _P3_SB_D3
	.globl _P3_SB_D2
	.globl _P3_SB_D1
	.globl _P3_SB_D0
	.globl _IEN0_SB_GLOBAL
	.globl _IEN0_SB_T2
	.globl _IEN0_SB_UART
	.globl _IEN0_SB_T1
	.globl _IEN0_SB_POFIRQ
	.globl _IEN0_SB_T0
	.globl _IEN0_SB_IFP
	.globl _P2_SB_D7
	.globl _P2_SB_D6
	.globl _P2_SB_D5
	.globl _P2_SB_D4
	.globl _P2_SB_D3
	.globl _P2_SB_D2
	.globl _P2_SB_D1
	.globl _P2_SB_D0
	.globl _S0CON_SB_SM0
	.globl _S0CON_SB_SM1
	.globl _S0CON_SB_SM20
	.globl _S0CON_SB_REN0
	.globl _S0CON_SB_TB80
	.globl _S0CON_SB_RB80
	.globl _S0CON_SB_TI0
	.globl _S0CON_SB_RI0
	.globl _P1_SB_D7
	.globl _P1_SB_D6
	.globl _P1_SB_D5
	.globl _P1_SB_D4
	.globl _P1_SB_D3
	.globl _P1_SB_D2
	.globl _P1_SB_D1
	.globl _P1_SB_D0
	.globl _TCON_SB_TF1
	.globl _TCON_SB_TR1
	.globl _TCON_SB_TF0
	.globl _TCON_SB_TR0
	.globl _TCON_SB_IE1
	.globl _TCON_SB_IT1
	.globl _TCON_SB_IE0
	.globl _TCON_SB_IT0
	.globl _P0_SB_D7
	.globl _P0_SB_D6
	.globl _P0_SB_D5
	.globl _P0_SB_D4
	.globl _P0_SB_D3
	.globl _P0_SB_D2
	.globl _P0_SB_D1
	.globl _P0_SB_D0
	.globl _ADCDAT
	.globl _S0REL
	.globl _T2
	.globl _T1
	.globl _T0
	.globl _CRC
	.globl _CC3
	.globl _CC2
	.globl _CC1
	.globl _SPIMDAT
	.globl _SPIMSTAT
	.globl _SPIMCON1
	.globl _SPIMCON0
	.globl _FCR
	.globl _FPCR
	.globl _FSR
	.globl _B
	.globl _ARCON
	.globl _MD5
	.globl _MD4
	.globl _MD3
	.globl _MD2
	.globl _MD1
	.globl _MD0
	.globl _RFCON
	.globl _SPIRDAT
	.globl _SPIRSTAT
	.globl _SPIRCON1
	.globl _SPIRCON0
	.globl _W2CON0
	.globl _W2CON1
	.globl _ACC
	.globl _CCPDATO
	.globl _CCPDATIB
	.globl _CCPDATIA
	.globl _POFCON
	.globl _COMPCON
	.globl _W2DAT
	.globl _W2SADR
	.globl _ADCON
	.globl _RNGDAT
	.globl _RNGCTL
	.globl _ADCDATL
	.globl _ADCDATH
	.globl _ADCCON1
	.globl _ADCCON2
	.globl _ADCCON3
	.globl _PSW
	.globl _WUOPC0
	.globl _WUOPC1
	.globl _TH2
	.globl _TL2
	.globl _CRCH
	.globl _CRCL
	.globl __XPAGE
	.globl _MPAGE
	.globl _T2CON
	.globl _CCH3
	.globl _CCL3
	.globl _CCH2
	.globl _CCL2
	.globl _CCH1
	.globl _CCL1
	.globl _CCEN
	.globl _IRCON
	.globl _SPISDAT
	.globl _SPISSTAT
	.globl _SPISCON1
	.globl _SPISCON0
	.globl _S0RELH
	.globl _IP1
	.globl _IEN1
	.globl _SPISRDSZ
	.globl _RTC2CPT00
	.globl _RTC2CMP1
	.globl _RTC2CMP0
	.globl _RTC2CON
	.globl _PWMCON
	.globl _RSTREAS
	.globl _P3
	.globl _WDSV
	.globl _OPMCON
	.globl _CLKLFCTRL
	.globl _RTC2CPT10
	.globl _RTC2CPT01
	.globl _S0RELL
	.globl _IP0
	.globl _IEN0
	.globl _MEMCON
	.globl _INTEXP
	.globl _WUCON
	.globl _PWRDWN
	.globl _CLKCTRL
	.globl _PWMDC1
	.globl _PWMDC0
	.globl _P2
	.globl _P1CON
	.globl _P0CON
	.globl _S0BUF
	.globl _S0CON
	.globl _P2CON
	.globl _P3DIR
	.globl _P2DIR
	.globl _P1DIR
	.globl _P0DIR
	.globl _DPS
	.globl _P1
	.globl _P3CON
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH1
	.globl _DPL1
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _mcs
	.globl _ml
	.globl _base_addr
	.globl _RF24write_PARM_4
	.globl _RF24write_PARM_3
	.globl _RF24write_PARM_2
	.globl _write_buf_PARM_3
	.globl _write_buf_PARM_2
	.globl _BuildApollonMessage_PARM_3
	.globl _BuildApollonMessage_PARM_2
	.globl _inMsg
	.globl _outMsg
	.globl _brightValue
	.globl _uvValue
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_DPL1	=	0x0084
_DPH1	=	0x0085
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P3CON	=	0x008f
_P1	=	0x0090
_DPS	=	0x0092
_P0DIR	=	0x0093
_P1DIR	=	0x0094
_P2DIR	=	0x0095
_P3DIR	=	0x0096
_P2CON	=	0x0097
_S0CON	=	0x0098
_S0BUF	=	0x0099
_P0CON	=	0x009e
_P1CON	=	0x009f
_P2	=	0x00a0
_PWMDC0	=	0x00a1
_PWMDC1	=	0x00a2
_CLKCTRL	=	0x00a3
_PWRDWN	=	0x00a4
_WUCON	=	0x00a5
_INTEXP	=	0x00a6
_MEMCON	=	0x00a7
_IEN0	=	0x00a8
_IP0	=	0x00a9
_S0RELL	=	0x00aa
_RTC2CPT01	=	0x00ab
_RTC2CPT10	=	0x00ac
_CLKLFCTRL	=	0x00ad
_OPMCON	=	0x00ae
_WDSV	=	0x00af
_P3	=	0x00b0
_RSTREAS	=	0x00b1
_PWMCON	=	0x00b2
_RTC2CON	=	0x00b3
_RTC2CMP0	=	0x00b4
_RTC2CMP1	=	0x00b5
_RTC2CPT00	=	0x00b6
_SPISRDSZ	=	0x00b7
_IEN1	=	0x00b8
_IP1	=	0x00b9
_S0RELH	=	0x00ba
_SPISCON0	=	0x00bc
_SPISCON1	=	0x00bd
_SPISSTAT	=	0x00be
_SPISDAT	=	0x00bf
_IRCON	=	0x00c0
_CCEN	=	0x00c1
_CCL1	=	0x00c2
_CCH1	=	0x00c3
_CCL2	=	0x00c4
_CCH2	=	0x00c5
_CCL3	=	0x00c6
_CCH3	=	0x00c7
_T2CON	=	0x00c8
_MPAGE	=	0x00c9
__XPAGE	=	0x00c9
_CRCL	=	0x00ca
_CRCH	=	0x00cb
_TL2	=	0x00cc
_TH2	=	0x00cd
_WUOPC1	=	0x00ce
_WUOPC0	=	0x00cf
_PSW	=	0x00d0
_ADCCON3	=	0x00d1
_ADCCON2	=	0x00d2
_ADCCON1	=	0x00d3
_ADCDATH	=	0x00d4
_ADCDATL	=	0x00d5
_RNGCTL	=	0x00d6
_RNGDAT	=	0x00d7
_ADCON	=	0x00d8
_W2SADR	=	0x00d9
_W2DAT	=	0x00da
_COMPCON	=	0x00db
_POFCON	=	0x00dc
_CCPDATIA	=	0x00dd
_CCPDATIB	=	0x00de
_CCPDATO	=	0x00df
_ACC	=	0x00e0
_W2CON1	=	0x00e1
_W2CON0	=	0x00e2
_SPIRCON0	=	0x00e4
_SPIRCON1	=	0x00e5
_SPIRSTAT	=	0x00e6
_SPIRDAT	=	0x00e7
_RFCON	=	0x00e8
_MD0	=	0x00e9
_MD1	=	0x00ea
_MD2	=	0x00eb
_MD3	=	0x00ec
_MD4	=	0x00ed
_MD5	=	0x00ee
_ARCON	=	0x00ef
_B	=	0x00f0
_FSR	=	0x00f8
_FPCR	=	0x00f9
_FCR	=	0x00fa
_SPIMCON0	=	0x00fc
_SPIMCON1	=	0x00fd
_SPIMSTAT	=	0x00fe
_SPIMDAT	=	0x00ff
_CC1	=	0xc3c2
_CC2	=	0xc5c4
_CC3	=	0xc7c6
_CRC	=	0xcbca
_T0	=	0x8c8a
_T1	=	0x8d8b
_T2	=	0xcdcc
_S0REL	=	0xbaaa
_ADCDAT	=	0xd4d5
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0_SB_D0	=	0x0080
_P0_SB_D1	=	0x0081
_P0_SB_D2	=	0x0082
_P0_SB_D3	=	0x0083
_P0_SB_D4	=	0x0084
_P0_SB_D5	=	0x0085
_P0_SB_D6	=	0x0086
_P0_SB_D7	=	0x0087
_TCON_SB_IT0	=	0x0088
_TCON_SB_IE0	=	0x0089
_TCON_SB_IT1	=	0x008a
_TCON_SB_IE1	=	0x008b
_TCON_SB_TR0	=	0x008c
_TCON_SB_TF0	=	0x008d
_TCON_SB_TR1	=	0x008e
_TCON_SB_TF1	=	0x008f
_P1_SB_D0	=	0x0090
_P1_SB_D1	=	0x0091
_P1_SB_D2	=	0x0092
_P1_SB_D3	=	0x0093
_P1_SB_D4	=	0x0094
_P1_SB_D5	=	0x0095
_P1_SB_D6	=	0x0096
_P1_SB_D7	=	0x0097
_S0CON_SB_RI0	=	0x0098
_S0CON_SB_TI0	=	0x0099
_S0CON_SB_RB80	=	0x009a
_S0CON_SB_TB80	=	0x009b
_S0CON_SB_REN0	=	0x009c
_S0CON_SB_SM20	=	0x009d
_S0CON_SB_SM1	=	0x009e
_S0CON_SB_SM0	=	0x009f
_P2_SB_D0	=	0x00a0
_P2_SB_D1	=	0x00a1
_P2_SB_D2	=	0x00a2
_P2_SB_D3	=	0x00a3
_P2_SB_D4	=	0x00a4
_P2_SB_D5	=	0x00a5
_P2_SB_D6	=	0x00a6
_P2_SB_D7	=	0x00a7
_IEN0_SB_IFP	=	0x00a8
_IEN0_SB_T0	=	0x00a9
_IEN0_SB_POFIRQ	=	0x00aa
_IEN0_SB_T1	=	0x00ab
_IEN0_SB_UART	=	0x00ac
_IEN0_SB_T2	=	0x00ad
_IEN0_SB_GLOBAL	=	0x00af
_P3_SB_D0	=	0x00b0
_P3_SB_D1	=	0x00b1
_P3_SB_D2	=	0x00b2
_P3_SB_D3	=	0x00b3
_P3_SB_D4	=	0x00b4
_P3_SB_D5	=	0x00b5
_P3_SB_D6	=	0x00b6
_P3_SB_D7	=	0x00b7
_IEN1_SB_RFRDY	=	0x00b8
_IEN1_SB_RFIRQ	=	0x00b9
_IEN1_SB_SPI_2WIRE	=	0x00ba
_IEN1_SB_WUOPIRQ	=	0x00bb
_IEN1_SB_MISCIRQ	=	0x00bc
_IEN1_SB_TICK	=	0x00bd
_IEN1_SB_T2EXTRLD	=	0x00bf
_IRCON_SB_RFRDY	=	0x00c0
_IRCON_SB_RFIRQ	=	0x00c1
_IRCON_SB_SPI_2WIRE	=	0x00c2
_IRCON_SB_WUOPIRQ	=	0x00c3
_IRCON_SB_MISCIRQ	=	0x00c4
_IRCON_SB_TICK	=	0x00c5
_IRCON_SB_TF2	=	0x00c6
_IRCON_SB_EXF2	=	0x00c7
_T2CON_SB_T2I0	=	0x00c8
_T2CON_SB_T2I1	=	0x00c9
_T2CON_SB_T2CM	=	0x00ca
_T2CON_SB_T2R0	=	0x00cb
_T2CON_SB_T2R1	=	0x00cc
_T2CON_SB_I2FR	=	0x00cd
_T2CON_SB_I3FR	=	0x00ce
_T2CON_SB_T2PS	=	0x00cf
_PSW_SB_CY	=	0x00d7
_PSW_SB_AC	=	0x00d6
_PSW_SB_F0	=	0x00d5
_PSW_SB_RS1	=	0x00d4
_PSW_SB_RS0	=	0x00d3
_PSW_SB_OV	=	0x00d2
_PSW_SB_F1	=	0x00d1
_PSW_SB_P	=	0x00d0
_ADCON_SB_BD	=	0x00df
_RFCON_SB_RFCE	=	0x00e8
_RFCON_SB_RFCSN	=	0x00e9
_RFCON_SB_RFCKEN	=	0x00ea
_FSR_SB_RDISMB	=	0x00fa
_FSR_SB_INFEN	=	0x00fb
_FSR_SB_RDYN	=	0x00fc
_FSR_SB_WEN	=	0x00fd
_FSR_SB_STP	=	0x00fe
_FSR_SB_ENDBG	=	0x00ff
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_process_time_sloc0_1_0:
	.ds 2
_process_type_sloc0_1_0:
	.ds 4
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
_uvValue::
	.ds 4
_brightValue::
	.ds 4
_outMsg::
	.ds 33
_inMsg::
	.ds 33
_BuildMessage_command_1_112:
	.ds 1
_BuildApollonMessage_PARM_2:
	.ds 4
_BuildApollonMessage_PARM_3:
	.ds 4
_BuildApollonMessage_command_1_114:
	.ds 1
_write_buf_PARM_2:
	.ds 1
_write_buf_PARM_3:
	.ds 1
_RF24write_PARM_2:
	.ds 3
_RF24write_PARM_3:
	.ds 1
_RF24write_PARM_4:
	.ds 1
_RF24write_nextnode_1_120:
	.ds 1
_RF24write_config_1_121:
	.ds 1
_getDynamicPayloadSize_result_1_127:
	.ds 1
_RF24readMessage_buf_1_129:
	.ds 3
_RF24readMessage_payload_length_1_130:
	.ds 1
_RF24readMessage_result_4_133:
	.ds 1
_process_rx_result_1_135:
	.ds 1
_process_time_wait_time_1_137:
	.ds 2
_process_type_response_1_140:
	.ds 1
_SendMessage_address_1_146:
	.ds 1
_RF24init_config_1_148:
	.ds 1
_setup_config_4_159:
	.ds 1
_main_config_7_173:
	.ds 1
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
_base_addr::
	.ds 5
_ml::
	.ds 4
_mcs::
	.ds 1
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
	reti
	.ds	7
	ljmp	_isrINTERRUPT_VECTOR_T0
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genXINIT
	.globl __mcs51_genXRAMCLEAR
	.globl __mcs51_genRAMCLEAR
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
__sdcc_program_startup:
	ljmp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'isrINTERRUPT_VECTOR_T0'
;------------------------------------------------------------
;	main.c:54: ISR(INTERRUPT_VECTOR_T0){
;	-----------------------------------------
;	 function isrINTERRUPT_VECTOR_T0
;	-----------------------------------------
_isrINTERRUPT_VECTOR_T0:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
	push	acc
	push	dpl
	push	dph
	push	ar7
	push	psw
	mov	psw,#0x00
;	main.c:55: TL0 = TLSTART;
	mov	_TL0,#0x22
;	main.c:56: if (mcs>=6) {
	mov	dptr,#_mcs
	movx	a,@dptr
	mov	r7,a
	cjne	r7,#0x06,00108$
00108$:
	jc	00102$
;	main.c:57: ml++;
	mov	dptr,#_ml
	movx	a,@dptr
	add	a,#0x01
	movx	@dptr,a
	inc	dptr
	movx	a,@dptr
	addc	a,#0x00
	movx	@dptr,a
	inc	dptr
	movx	a,@dptr
	addc	a,#0x00
	movx	@dptr,a
	inc	dptr
	movx	a,@dptr
	addc	a,#0x00
	movx	@dptr,a
;	main.c:58: mcs=0;
	mov	dptr,#_mcs
	clr	a
	movx	@dptr,a
00102$:
;	main.c:60: mcs++;
	mov	dptr,#_mcs
	movx	a,@dptr
	add	a,#0x01
	movx	@dptr,a
	pop	psw
	pop	ar7
	pop	dph
	pop	dpl
	pop	acc
	reti
;	eliminated unneeded push/pop b
;------------------------------------------------------------
;Allocation info for local variables in function 'BuildMessage'
;------------------------------------------------------------
;command                   Allocated with name '_BuildMessage_command_1_112'
;------------------------------------------------------------
;	main.c:70: void BuildMessage(uint8_t command) {
;	-----------------------------------------
;	 function BuildMessage
;	-----------------------------------------
_BuildMessage:
	mov	a,dpl
	mov	dptr,#_BuildMessage_command_1_112
	movx	@dptr,a
;	main.c:71: outMsg.message.command = command;
	movx	a,@dptr
	mov	dptr,#_outMsg
	movx	@dptr,a
;	main.c:72: outMsg.message.cardType = LUMINOS_TYPE;
	mov	dptr,#(_outMsg + 0x0001)
	mov	a,#0x01
	movx	@dptr,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'BuildApollonMessage'
;------------------------------------------------------------
;uvValue                   Allocated with name '_BuildApollonMessage_PARM_2'
;brightValue               Allocated with name '_BuildApollonMessage_PARM_3'
;command                   Allocated with name '_BuildApollonMessage_command_1_114'
;------------------------------------------------------------
;	main.c:75: void BuildApollonMessage(uint8_t command, uint32_t uvValue, uint32_t brightValue) {
;	-----------------------------------------
;	 function BuildApollonMessage
;	-----------------------------------------
_BuildApollonMessage:
	mov	a,dpl
	mov	dptr,#_BuildApollonMessage_command_1_114
	movx	@dptr,a
;	main.c:76: outMsg.message.command = command;
	movx	a,@dptr
	mov	dptr,#_outMsg
	movx	@dptr,a
;	main.c:77: outMsg.message.cardType = LUMINOS_TYPE;
	mov	dptr,#(_outMsg + 0x0001)
	mov	a,#0x01
	movx	@dptr,a
;	main.c:78: outMsg.message.messageType.apollonMessage.apollonMessageStruct.sensor1 = UV;
	mov	dptr,#(_outMsg + 0x0002)
	mov	a,#0x0c
	movx	@dptr,a
;	main.c:79: outMsg.message.messageType.apollonMessage.apollonMessageStruct.uvValue= uvValue;
	mov	dptr,#_BuildApollonMessage_PARM_2
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
	mov	dptr,#(_outMsg + 0x0003)
	mov	a,r4
	movx	@dptr,a
	mov	a,r5
	inc	dptr
	movx	@dptr,a
	mov	a,r6
	inc	dptr
	movx	@dptr,a
	mov	a,r7
	inc	dptr
	movx	@dptr,a
;	main.c:80: outMsg.message.messageType.apollonMessage.apollonMessageStruct.sensor2 = BRIGHTNESS;
	mov	dptr,#(_outMsg + 0x0007)
	mov	a,#0x04
	movx	@dptr,a
;	main.c:81: outMsg.message.messageType.apollonMessage.apollonMessageStruct.brigthValue = brightValue;
	mov	dptr,#_BuildApollonMessage_PARM_3
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
	mov	dptr,#(_outMsg + 0x0008)
	mov	a,r4
	movx	@dptr,a
	mov	a,r5
	inc	dptr
	movx	@dptr,a
	mov	a,r6
	inc	dptr
	movx	@dptr,a
	mov	a,r7
	inc	dptr
	movx	@dptr,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'flush_fifo_irq'
;------------------------------------------------------------
;	main.c:104: void flush_fifo_irq() {
;	-----------------------------------------
;	 function flush_fifo_irq
;	-----------------------------------------
_flush_fifo_irq:
;	main.c:105: rf_flush_tx();
	mov	dptr,#_rf_spi_execute_command_PARM_2
	clr	a
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_3
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_4
	inc	a
	movx	@dptr,a
	mov	dpl,#0xe1
	lcall	_rf_spi_execute_command
;	main.c:106: rf_flush_rx();
	mov	dptr,#_rf_spi_execute_command_PARM_2
	clr	a
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_3
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_4
	inc	a
	movx	@dptr,a
	mov	dpl,#0xe2
	lcall	_rf_spi_execute_command
;	main.c:107: rf_irq_clear_all();
	ljmp	_rf_irq_clear_all
;------------------------------------------------------------
;Allocation info for local variables in function 'RF24write'
;------------------------------------------------------------
;buf                       Allocated with name '_RF24write_PARM_2'
;len                       Allocated with name '_RF24write_PARM_3'
;broadcast                 Allocated with name '_RF24write_PARM_4'
;nextnode                  Allocated with name '_RF24write_nextnode_1_120'
;__00010013                Allocated with name '_RF24write___00010013_4_124'
;config                    Allocated with name '_RF24write_config_1_121'
;result                    Allocated with name '_RF24write_result_1_121'
;__00020014                Allocated with name '_RF24write___00020014_3_123'
;__00020015                Allocated with name '_RF24write___00020015_3_123'
;__00020016                Allocated with name '_RF24write___00020016_3_123'
;buf                       Allocated with name '_RF24write_buf_3_123'
;len                       Allocated with name '_RF24write_len_3_123'
;broadcast                 Allocated with name '_RF24write_broadcast_3_123'
;FIFO_STATUS               Allocated with name '_RF24write_FIFO_STATUS_4_124'
;status                    Allocated with name '_RF24write_status_4_124'
;------------------------------------------------------------
;	main.c:110: bool RF24write(uint8_t nextnode, uint8_t* buf, uint8_t len, bool broadcast) {
;	-----------------------------------------
;	 function RF24write
;	-----------------------------------------
_RF24write:
	mov	a,dpl
	mov	dptr,#_RF24write_nextnode_1_120
	movx	@dptr,a
;	main.c:115: rf_clear_ce();
	clr	_RFCON_SB_RFCE 
;	main.c:117: config = RF_CONFIG_PWR_UP | RF_CONFIG_CRCO | RF_CONFIG_EN_CRC;
	mov	dptr,#_RF24write_config_1_121
	mov	a,#0x0e
	movx	@dptr,a
;	main.c:118: rf_write_register(RF_CONFIG,&config,1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_RF24write_config_1_121
	movx	@dptr,a
	mov	a,#(_RF24write_config_1_121 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x00
	lcall	_rf_write_register
;	main.c:120: flush_fifo_irq();
	lcall	_flush_fifo_irq
;	main.c:122: base_addr[0] = nextnode;
	mov	dptr,#_RF24write_nextnode_1_120
	movx	a,@dptr
	mov	r7,a
	mov	dptr,#_base_addr
	movx	@dptr,a
;	main.c:123: rf_set_tx_addr(base_addr, 5);
	mov	dptr,#_rf_set_tx_addr_PARM_2
	mov	a,#0x05
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_base_addr
	mov	b,#0x00
	push	ar7
	lcall	_rf_set_tx_addr
	pop	ar7
;	main.c:125: base_addr[0] = nextnode;
	mov	dptr,#_base_addr
	mov	a,r7
	movx	@dptr,a
;	main.c:126: rf_set_rx_addr(base_addr, 5, 0);
	mov	dptr,#_rf_set_rx_addr_PARM_2
	mov	a,#0x05
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_set_rx_addr_PARM_3
	movx	@dptr,a
	mov	dptr,#_base_addr
	mov	b,#0x00
	push	ar7
	lcall	_rf_set_rx_addr
	pop	ar7
;	main.c:129: result = write_buf(buf, len, broadcast);
	mov	dptr,#_RF24write_PARM_4
	movx	a,@dptr
	mov	r6,a
	mov	dptr,#_RF24write_PARM_3
	movx	a,@dptr
	mov	r5,a
	mov	dptr,#_RF24write_PARM_2
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;	main.c:88: uint8_t status = rf_spi_execute_command(broadcast ? RF_W_TX_PAYLOAD_NOACK : RF_W_TX_PAYLOAD, buf, len, false);
	mov	a,r6
	jz	00108$
	mov	r6,#0xb0
	sjmp	00109$
00108$:
	mov	r6,#0xa0
00109$:
	mov	ar1,r5
	mov	r5,#0x00
	mov	dptr,#_rf_spi_execute_command_PARM_2
	mov	a,r2
	movx	@dptr,a
	mov	a,r3
	inc	dptr
	movx	@dptr,a
	mov	a,r4
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_3
	mov	a,r1
	movx	@dptr,a
	mov	a,r5
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_4
	movx	@dptr,a
	mov	dpl,r6
	push	ar7
	lcall	_rf_spi_execute_command
	pop	ar7
;	main.c:90: rf_set_ce();
	setb	_RFCON_SB_RFCE 
	mov	dptr,#0x0004
	push	ar7
	lcall	_delay_us
;	main.c:92: delay_us(CE_PULSE_LENGTH);
	mov	dptr,#0x000a
	lcall	_delay_us
	pop	ar7
;	main.c:94: rf_clear_ce();
	clr	_RFCON_SB_RFCE 
;	main.c:96: do {
00101$:
;	main.c:98: FIFO_STATUS = rf_get_status();
	mov	dptr,#_rf_spi_execute_command_PARM_2
	clr	a
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_3
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_4
	inc	a
	movx	@dptr,a
	mov	dpl,#0xff
	push	ar7
	lcall	_rf_spi_execute_command
	mov	r6,dpl
	pop	ar7
;	main.c:99: } while( !(FIFO_STATUS & RF_STATUS_TX_DS) && !(FIFO_STATUS & RF_STATUS_MAX_RT) );
	mov	a,r6
	jb	acc.5,00104$
	mov	a,r6
	jnb	acc.4,00101$
00104$:
;	main.c:101: return (FIFO_STATUS & RF_STATUS_TX_DS);
	anl	ar6,#0x20
;	main.c:131: config = RF_CONFIG_PWR_UP | RF_CONFIG_CRCO | RF_CONFIG_EN_CRC | RF_CONFIG_PRIM_RX;
	mov	dptr,#_RF24write_config_1_121
	mov	a,#0x0f
	movx	@dptr,a
;	main.c:132: rf_write_register(RF_CONFIG,&config,1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_RF24write_config_1_121
	movx	@dptr,a
	mov	a,#(_RF24write_config_1_121 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x00
	push	ar7
	push	ar6
	lcall	_rf_write_register
	pop	ar6
	pop	ar7
;	main.c:134: base_addr[0] = nextnode;
	mov	dptr,#_base_addr
	mov	a,r7
	movx	@dptr,a
;	main.c:135: rf_set_rx_addr(base_addr, 5, 0);
	mov	dptr,#_rf_set_rx_addr_PARM_2
	mov	a,#0x05
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_set_rx_addr_PARM_3
	movx	@dptr,a
	mov	dptr,#_base_addr
	mov	b,#0x00
	push	ar6
	lcall	_rf_set_rx_addr
;	main.c:138: flush_fifo_irq();
	lcall	_flush_fifo_irq
	pop	ar6
;	main.c:140: rf_set_ce();
	setb	_RFCON_SB_RFCE 
	mov	dptr,#0x0004
	push	ar6
	lcall	_delay_us
;	main.c:142: delay_us(130);
	mov	dptr,#0x0082
	lcall	_delay_us
	pop	ar6
;	main.c:144: return result;
	mov	dpl,r6
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'RF24readMessage'
;------------------------------------------------------------
;buf                       Allocated with name '_RF24readMessage_buf_1_129'
;__00010018                Allocated with name '_RF24readMessage___00010018_4_133'
;payload_length            Allocated with name '_RF24readMessage_payload_length_1_130'
;result                    Allocated with name '_RF24readMessage_result_4_133'
;------------------------------------------------------------
;	main.c:162: uint8_t RF24readMessage(uint8_t* buf) {
;	-----------------------------------------
;	 function RF24readMessage
;	-----------------------------------------
_RF24readMessage:
	mov	r7,b
	mov	r6,dph
	mov	a,dpl
	mov	dptr,#_RF24readMessage_buf_1_129
	movx	@dptr,a
	mov	a,r6
	inc	dptr
	movx	@dptr,a
	mov	a,r7
	inc	dptr
	movx	@dptr,a
;	main.c:164: uint8_t payload_length = getDynamicPayloadSize();
	mov	dptr,#_RF24readMessage_result_4_133
	mov	b,#0x00
	lcall	_rf_read_rx_payload_width
	mov	dptr,#_RF24readMessage_result_4_133
	movx	a,@dptr
	mov  r7,a
	add	a,#0xff - 0x20
	jnc	00102$
	mov	dptr,#_rf_spi_execute_command_PARM_2
	clr	a
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_3
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_4
	inc	a
	movx	@dptr,a
	mov	dpl,#0xe2
	lcall	_rf_spi_execute_command
	mov	dptr,#_RF24readMessage_result_4_133
	clr	a
	movx	@dptr,a
00102$:
	mov	dptr,#_RF24readMessage_result_4_133
	movx	a,@dptr
	mov	r7,a
	mov	dptr,#_RF24readMessage_payload_length_1_130
	movx	@dptr,a
;	main.c:166: rf_read_rx_payload(buf,payload_length);
	mov	dptr,#_RF24readMessage_buf_1_129
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	mov	dptr,#_rf_read_rx_payload_PARM_2
	mov	a,r7
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	lcall	_rf_read_rx_payload
;	main.c:168: rf_irq_clear_all();
	lcall	_rf_irq_clear_all
;	main.c:169: return payload_length;
	mov	dptr,#_RF24readMessage_payload_length_1_130
	movx	a,@dptr
	mov	dpl,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'process_rx'
;------------------------------------------------------------
;result                    Allocated with name '_process_rx_result_1_135'
;------------------------------------------------------------
;	main.c:173: uint8_t process_rx() {
;	-----------------------------------------
;	 function process_rx
;	-----------------------------------------
_process_rx:
;	main.c:174: uint8_t result = 0xFF;
	mov	dptr,#_process_rx_result_1_135
	mov	a,#0xff
	movx	@dptr,a
;	main.c:175: if ( RF24available() ) {
	mov	dptr,#_rf_spi_execute_command_PARM_2
	clr	a
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_3
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_4
	inc	a
	movx	@dptr,a
	mov	dpl,#0xff
	lcall	_rf_spi_execute_command
	mov	a,dpl
	jnb	acc.6,00102$
;	main.c:176: RF24readMessage(inMsg.array);
	mov	dptr,#_inMsg
	mov	b,#0x00
	lcall	_RF24readMessage
;	main.c:177: result = inMsg.message.command;
	mov	dptr,#_inMsg
	movx	a,@dptr
	mov	r7,a
	mov	dptr,#_process_rx_result_1_135
	movx	@dptr,a
00102$:
;	main.c:179: return result;
	mov	dptr,#_process_rx_result_1_135
	movx	a,@dptr
	mov	dpl,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'process_time'
;------------------------------------------------------------
;sloc0                     Allocated with name '_process_time_sloc0_1_0'
;wait_time                 Allocated with name '_process_time_wait_time_1_137'
;entry                     Allocated with name '_process_time_entry_1_138'
;------------------------------------------------------------
;	main.c:183: void process_time(uint16_t wait_time) {
;	-----------------------------------------
;	 function process_time
;	-----------------------------------------
_process_time:
	mov	r7,dph
	mov	a,dpl
	mov	dptr,#_process_time_wait_time_1_137
	movx	@dptr,a
	mov	a,r7
	inc	dptr
	movx	@dptr,a
;	main.c:184: unsigned long entry = millis();
	mov	dptr,#_ml
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;	main.c:185: while ( (ml < entry+wait_time) ) {
	mov	dptr,#_process_time_wait_time_1_137
	movx	a,@dptr
	mov	_process_time_sloc0_1_0,a
	inc	dptr
	movx	a,@dptr
	mov	(_process_time_sloc0_1_0 + 1),a
00101$:
	mov	r0,_process_time_sloc0_1_0
	mov	r1,(_process_time_sloc0_1_0 + 1)
	clr	a
	mov	r2,a
	mov	r3,a
	mov	a,r0
	add	a,r4
	mov	r0,a
	mov	a,r1
	addc	a,r5
	mov	r1,a
	mov	a,r2
	addc	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	push	ar4
	push	ar5
	push	ar6
	push	ar7
	mov	dptr,#_ml
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	a,r5
	subb	a,r1
	mov	a,r6
	subb	a,r2
	mov	a,r7
	subb	a,r3
	pop	ar7
	pop	ar6
	pop	ar5
	pop	ar4
	jnc	00104$
;	main.c:186: process_rx();
	push	ar7
	push	ar6
	push	ar5
	push	ar4
	lcall	_process_rx
	pop	ar4
	pop	ar5
	pop	ar6
	pop	ar7
	sjmp	00101$
00104$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'process_type'
;------------------------------------------------------------
;sloc0                     Allocated with name '_process_type_sloc0_1_0'
;response                  Allocated with name '_process_type_response_1_140'
;res_type                  Allocated with name '_process_type_res_type_1_141'
;entry                     Allocated with name '_process_type_entry_1_141'
;__00020020                Allocated with name '_process_type___00020020_5_145'
;__00030021                Allocated with name '_process_type___00030021_4_144'
;sec                       Allocated with name '_process_type_sec_4_144'
;------------------------------------------------------------
;	main.c:190: bool process_type(uint8_t response) {
;	-----------------------------------------
;	 function process_type
;	-----------------------------------------
_process_type:
	mov	a,dpl
	mov	dptr,#_process_type_response_1_140
	movx	@dptr,a
;	main.c:192: unsigned long entry = millis();
	mov	dptr,#_ml
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;	main.c:193: do {
	mov	dptr,#_process_type_response_1_140
	movx	a,@dptr
	mov	r3,a
	mov	a,#0x40
	add	a,r4
	mov	_process_type_sloc0_1_0,a
	mov	a,#0x1f
	addc	a,r5
	mov	(_process_type_sloc0_1_0 + 1),a
	clr	a
	addc	a,r6
	mov	(_process_type_sloc0_1_0 + 2),a
	clr	a
	addc	a,r7
	mov	(_process_type_sloc0_1_0 + 3),a
00102$:
;	main.c:195: res_type = process_rx();
	push	ar3
	push	ar3
	lcall	_process_rx
	mov	r2,dpl
	pop	ar3
;	main.c:196: } while ( (ml < entry+8000) && (res_type!=response) );
	mov	dptr,#_ml
	movx	a,@dptr
	mov	r0,a
	inc	dptr
	movx	a,@dptr
	mov	r1,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
	clr	c
	mov	a,r0
	subb	a,_process_type_sloc0_1_0
	mov	a,r1
	subb	a,(_process_type_sloc0_1_0 + 1)
	mov	a,r3
	subb	a,(_process_type_sloc0_1_0 + 2)
	mov	a,r7
	subb	a,(_process_type_sloc0_1_0 + 3)
	pop	ar3
	jnc	00104$
	mov	a,r2
	cjne	a,ar3,00102$
00104$:
;	main.c:198: return (res_type==response);
	mov	dptr,#_process_type_response_1_140
	movx	a,@dptr
	mov	r7,a
	mov	a,r2
	cjne	a,ar7,00117$
	mov	a,#0x01
	sjmp	00118$
00117$:
	clr	a
00118$:
	mov	dpl,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SendMessage'
;------------------------------------------------------------
;address                   Allocated with name '_SendMessage_address_1_146'
;------------------------------------------------------------
;	main.c:201: bool SendMessage(uint8_t address) {
;	-----------------------------------------
;	 function SendMessage
;	-----------------------------------------
_SendMessage:
	mov	a,dpl
	mov	dptr,#_SendMessage_address_1_146
	movx	@dptr,a
;	main.c:202: return RF24write(address, outMsg.array, APOLLON_SIZE, (address == BROADCAST_ADDRESS) );
	movx	a,@dptr
	mov	r7,a
	mov	dptr,#_RF24write_PARM_2
	mov	a,#_outMsg
	movx	@dptr,a
	mov	a,#(_outMsg >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	cjne	r7,#0xff,00103$
	inc	a
	sjmp	00104$
00103$:
	clr	a
00104$:
	mov	r6,a
	mov	dptr,#_RF24write_PARM_3
	mov	a,#0x0a
	movx	@dptr,a
	mov	dptr,#_RF24write_PARM_4
	mov	a,r6
	movx	@dptr,a
	mov	dpl,r7
	ljmp	_RF24write
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;__00010030                Allocated with name '_main___00010030_4_179'
;__00010024                Allocated with name '_main___00010024_4_163'
;__00020025                Allocated with name '_main___00020025_5_168'
;sec                       Allocated with name '_main_sec_6_169'
;config                    Allocated with name '_main_config_7_173'
;__00020031                Allocated with name '_main___00020031_3_178'
;sec                       Allocated with name '_main_sec_3_178'
;------------------------------------------------------------
;	main.c:252: void main(){
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	../nRF24LE1_SDK/include/inline/watchdog_setup.inc:11: if (!pwr_clk_mgmt_is_clklf_enabled())
	mov	a,#0x07
	anl	a,_CLKLFCTRL
	mov	r7,a
	cjne	r7,#0x07,00106$
;	../nRF24LE1_SDK/include/inline/watchdog_setup.inc:14: pwr_clk_mgmt_clklf_configure(PWR_CLK_MGMT_CLKLF_CONFIG_OPTION_CLK_SRC_RCOSC32K);
	mov	dpl,#0x01
	lcall	_pwr_clk_mgmt_clklf_configure
;	../nRF24LE1_SDK/include/inline/watchdog_setup.inc:15: pwr_clk_mgmt_wait_until_clklf_is_ready();
00101$:
	mov	a,_CLKLFCTRL
	jnb	acc.6,00101$
;	main.c:236: watchdog_setup();
00106$:
;	main.c:244: );
	mov	dptr,#0xe00c
	lcall	_adc_configure
;	main.c:246: pinMode(GPIO_PIN_ID_P0_0, OUTPUT);
	mov	dptr,#_gpio_pin_configure_PARM_2
	mov	a,#0x01
	movx	@dptr,a
	mov	dpl,#0x00
	lcall	_gpio_pin_configure
;	main.c:208: rf_spi_configure_enable();
	lcall	_rf_spi_configure_enable
;	main.c:209: config = RF_EN_AA_ENAA_P0;
	mov	dptr,#_main_config_7_173
	mov	a,#0x01
	movx	@dptr,a
;	main.c:210: rf_write_register(RF_EN_AA, &config, 1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x01
	lcall	_rf_write_register
;	main.c:211: config = RF_EN_RXADDR_ERX_P0;
	mov	dptr,#_main_config_7_173
	mov	a,#0x01
	movx	@dptr,a
;	main.c:212: rf_write_register(RF_EN_RXADDR, &config, 1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x02
	lcall	_rf_write_register
;	main.c:213: config = RF_SETUP_AW_5BYTES;
	mov	dptr,#_main_config_7_173
	mov	a,#0x03
	movx	@dptr,a
;	main.c:214: rf_write_register(RF_SETUP_AW, &config, 1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x03
	lcall	_rf_write_register
;	main.c:215: config = RF_SETUP_RETR_ARD_1500 | RF_SETUP_RETR_ARC_5;
	mov	dptr,#_main_config_7_173
	mov	a,#0x55
	movx	@dptr,a
;	main.c:216: rf_write_register(RF_SETUP_RETR, &config, 1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x04
	lcall	_rf_write_register
;	main.c:217: config = RF24_CHANNEL;
	mov	dptr,#_main_config_7_173
	mov	a,#0x54
	movx	@dptr,a
;	main.c:218: rf_write_register(RF_RF_CH, &config, 1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x05
	lcall	_rf_write_register
;	main.c:219: config = RF24_PA_LEVEL | RF24_DATARATE;
	mov	dptr,#_main_config_7_173
	mov	a,#0x26
	movx	@dptr,a
;	main.c:220: rf_write_register(RF_RF_SETUP, &config, 1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x06
	lcall	_rf_write_register
;	main.c:222: config = 0x73;
	mov	dptr,#_main_config_7_173
	mov	a,#0x73
	movx	@dptr,a
;	main.c:223: rf_spi_execute_command(ACTIVATE,&config,1,false);
	mov	dptr,#_rf_spi_execute_command_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_spi_execute_command_PARM_4
	movx	@dptr,a
	mov	dpl,#0x50
	lcall	_rf_spi_execute_command
;	main.c:225: config = RF_DYNPD_DPL_P0;
	mov	dptr,#_main_config_7_173
	mov	a,#0x01
	movx	@dptr,a
;	main.c:226: rf_write_register(RF_DYNPD, &config, 1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x1c
	lcall	_rf_write_register
;	main.c:227: config = RF_FEATURE_EN_DPL | RF_FEATURE_EN_ACK_PAY;
	mov	dptr,#_main_config_7_173
	mov	a,#0x06
	movx	@dptr,a
;	main.c:228: rf_write_register(RF_FEATURE, &config, 1);
	mov	dptr,#_rf_write_register_PARM_2
	mov	a,#_main_config_7_173
	movx	@dptr,a
	mov	a,#(_main_config_7_173 >> 8)
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_rf_write_register_PARM_3
	inc	a
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x1d
	lcall	_rf_write_register
;	main.c:229: rf_power_up_param(false, RF_CONFIG_PWR_UP | RF_CONFIG_CRCO | RF_CONFIG_EN_CRC);
	mov	dptr,#_rf_power_up_param_PARM_2
	mov	a,#0x0e
	movx	@dptr,a
	mov	dpl,#0x00
	lcall	_rf_power_up_param
;	main.c:231: delay_us(130);
	mov	dptr,#0x0082
	lcall	_delay_us
;	main.c:64: interrupt_control_global_enable();
	setb	_IEN0_SB_GLOBAL 
;	main.c:65: interrupt_control_t0_enable();
	setb	_IEN0_SB_T0 
;	main.c:66: timer0_configure(TIMER0_CONFIG_OPTION_MODE_3_TWO_8_BIT_CTRS_TMRS,TLSTART);
	mov	dptr,#_timer0_configure_PARM_2
	mov	a,#0x22
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x03
	lcall	_timer0_configure
;	main.c:67: timer0_run();
	setb	_TCON_SB_TR0 
;	main.c:260: BuildMessage(CONFIGURATION);
	mov	dpl,#0x00
	lcall	_BuildMessage
;	main.c:261: SendMessage(BROADCAST_ADDRESS);
	mov	dpl,#0xff
	lcall	_SendMessage
;	main.c:262: process_type(CONFIGURATION);
	mov	dpl,#0x00
	lcall	_process_type
;	main.c:264: BuildMessage(ASK_SEND_DATA);
	mov	dpl,#0x01
	lcall	_BuildMessage
;	main.c:265: SendMessage(BROADCAST_ADDRESS);
	mov	dpl,#0xff
	lcall	_SendMessage
;	main.c:266: process_type(ASK_SEND_DATA);
	mov	dpl,#0x01
	lcall	_process_type
;	main.c:270: uvValue = 3;
	mov	dptr,#_uvValue
	mov	a,#0x03
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
;	main.c:271: brightValue =  521;
	mov	dptr,#_brightValue
	mov	a,#0x09
	movx	@dptr,a
	mov	a,#0x02
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
;	main.c:272: BuildApollonMessage(SEND_DATA,uvValue,brightValue);
	mov	dptr,#_BuildApollonMessage_PARM_2
	mov	a,#0x03
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dptr,#_BuildApollonMessage_PARM_3
	mov	a,#0x09
	movx	@dptr,a
	mov	a,#0x02
	inc	dptr
	movx	@dptr,a
	clr	a
	inc	dptr
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
	mov	dpl,#0x02
	lcall	_BuildApollonMessage
;	main.c:273: SendMessage(BROADCAST_ADDRESS);
	mov	dpl,#0xff
	lcall	_SendMessage
;	main.c:274: process_type(SEND_DATA);
	mov	dpl,#0x02
	lcall	_process_type
;	main.c:275: process_time(1000);
	mov	dptr,#0x03e8
	ljmp	_process_time
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
__xinit__base_addr:
	.db #0xff	; 255
	.db #0xfc	; 252
	.db #0xe1	; 225
	.db #0xa8	; 168
	.db #0xa8	; 168
__xinit__ml:
	.byte #0x00,#0x00,#0x00,#0x00	; 0
__xinit__mcs:
	.db #0x00	; 0
	.area CABS    (ABS,CODE)
