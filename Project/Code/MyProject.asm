
_update_traffic_lights:

	BTFSS      RE0_bit+0, BitPos(RE0_bit+0)
	GOTO       L_update_traffic_lights2
	MOVF       _exiting_manual+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_update_traffic_lights2
L__update_traffic_lights71:
	GOTO       L_update_traffic_lights3
L_update_traffic_lights5:
	BSF        RD2_bit+0, BitPos(RD2_bit+0)
	BCF        RD1_bit+0, BitPos(RD1_bit+0)
	BCF        RD0_bit+0, BitPos(RD0_bit+0)
	BCF        RD5_bit+0, BitPos(RD5_bit+0)
	BCF        RD4_bit+0, BitPos(RD4_bit+0)
	BSF        RD3_bit+0, BitPos(RD3_bit+0)
	GOTO       L_update_traffic_lights4
L_update_traffic_lights6:
	BCF        RD2_bit+0, BitPos(RD2_bit+0)
	BSF        RD1_bit+0, BitPos(RD1_bit+0)
	BCF        RD0_bit+0, BitPos(RD0_bit+0)
	BCF        RD5_bit+0, BitPos(RD5_bit+0)
	BCF        RD4_bit+0, BitPos(RD4_bit+0)
	BSF        RD3_bit+0, BitPos(RD3_bit+0)
	GOTO       L_update_traffic_lights4
L_update_traffic_lights7:
	BCF        RD2_bit+0, BitPos(RD2_bit+0)
	BCF        RD1_bit+0, BitPos(RD1_bit+0)
	BSF        RD0_bit+0, BitPos(RD0_bit+0)
	BSF        RD5_bit+0, BitPos(RD5_bit+0)
	BCF        RD4_bit+0, BitPos(RD4_bit+0)
	BCF        RD3_bit+0, BitPos(RD3_bit+0)
	GOTO       L_update_traffic_lights4
L_update_traffic_lights8:
	BCF        RD2_bit+0, BitPos(RD2_bit+0)
	BCF        RD1_bit+0, BitPos(RD1_bit+0)
	BSF        RD0_bit+0, BitPos(RD0_bit+0)
	BCF        RD5_bit+0, BitPos(RD5_bit+0)
	BSF        RD4_bit+0, BitPos(RD4_bit+0)
	BCF        RD3_bit+0, BitPos(RD3_bit+0)
	GOTO       L_update_traffic_lights4
L_update_traffic_lights3:
	MOVF       _state+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_update_traffic_lights5
	MOVF       _state+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_update_traffic_lights6
	MOVF       _state+0, 0
	XORLW      2
	BTFSC      STATUS+0, 2
	GOTO       L_update_traffic_lights7
	MOVF       _state+0, 0
	XORLW      3
	BTFSC      STATUS+0, 2
	GOTO       L_update_traffic_lights8
L_update_traffic_lights4:
	GOTO       L_update_traffic_lights9
L_update_traffic_lights2:
	GOTO       L_update_traffic_lights10
L_update_traffic_lights12:
	CLRF       _west_timer+0
	CLRF       _south_timer+0
	BSF        RD2_bit+0, BitPos(RD2_bit+0)
	BCF        RD1_bit+0, BitPos(RD1_bit+0)
	BCF        RD0_bit+0, BitPos(RD0_bit+0)
	BCF        RD5_bit+0, BitPos(RD5_bit+0)
	BCF        RD4_bit+0, BitPos(RD4_bit+0)
	BSF        RD3_bit+0, BitPos(RD3_bit+0)
	GOTO       L_update_traffic_lights11
L_update_traffic_lights13:
	CLRF       _south_timer+0
	BCF        RD2_bit+0, BitPos(RD2_bit+0)
	BSF        RD1_bit+0, BitPos(RD1_bit+0)
	BCF        RD0_bit+0, BitPos(RD0_bit+0)
	BCF        RD5_bit+0, BitPos(RD5_bit+0)
	BCF        RD4_bit+0, BitPos(RD4_bit+0)
	BSF        RD3_bit+0, BitPos(RD3_bit+0)
	GOTO       L_update_traffic_lights11
L_update_traffic_lights14:
	CLRF       _west_timer+0
	CLRF       _south_timer+0
	BCF        RD2_bit+0, BitPos(RD2_bit+0)
	BCF        RD1_bit+0, BitPos(RD1_bit+0)
	BSF        RD0_bit+0, BitPos(RD0_bit+0)
	BSF        RD5_bit+0, BitPos(RD5_bit+0)
	BCF        RD4_bit+0, BitPos(RD4_bit+0)
	BCF        RD3_bit+0, BitPos(RD3_bit+0)
	GOTO       L_update_traffic_lights11
L_update_traffic_lights15:
	CLRF       _west_timer+0
	BCF        RD2_bit+0, BitPos(RD2_bit+0)
	BCF        RD1_bit+0, BitPos(RD1_bit+0)
	BSF        RD0_bit+0, BitPos(RD0_bit+0)
	BCF        RD5_bit+0, BitPos(RD5_bit+0)
	BSF        RD4_bit+0, BitPos(RD4_bit+0)
	BCF        RD3_bit+0, BitPos(RD3_bit+0)
	GOTO       L_update_traffic_lights11
L_update_traffic_lights10:
	MOVF       _manual_state+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_update_traffic_lights12
	MOVF       _manual_state+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_update_traffic_lights13
	MOVF       _manual_state+0, 0
	XORLW      2
	BTFSC      STATUS+0, 2
	GOTO       L_update_traffic_lights14
	MOVF       _manual_state+0, 0
	XORLW      3
	BTFSC      STATUS+0, 2
	GOTO       L_update_traffic_lights15
L_update_traffic_lights11:
L_update_traffic_lights9:
L_end_update_traffic_lights:
	RETURN
; end of _update_traffic_lights

_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

	BTFSS      TMR0IF_bit+0, BitPos(TMR0IF_bit+0)
	GOTO       L_interrupt16
	MOVLW      6
	MOVWF      TMR0+0
	BCF        TMR0IF_bit+0, BitPos(TMR0IF_bit+0)
	BCF        RC0_bit+0, BitPos(RC0_bit+0)
	BCF        RC1_bit+0, BitPos(RC1_bit+0)
	BCF        RC2_bit+0, BitPos(RC2_bit+0)
	BCF        RC3_bit+0, BitPos(RC3_bit+0)
	CLRF       PORTB+0
	GOTO       L_interrupt17
L_interrupt19:
	MOVLW      10
	MOVWF      R4+0
	MOVF       _west_timer+0, 0
	MOVWF      R0+0
	CALL       _Div_8X8_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      PORTB+0
	BSF        RC0_bit+0, BitPos(RC0_bit+0)
	MOVLW      1
	MOVWF      _digit_select+0
	GOTO       L_interrupt18
L_interrupt20:
	MOVLW      10
	MOVWF      R4+0
	MOVF       _west_timer+0, 0
	MOVWF      R0+0
	CALL       _Div_8X8_U+0
	MOVF       R0+0, 0
	MOVWF      PORTB+0
	BSF        RC1_bit+0, BitPos(RC1_bit+0)
	MOVLW      2
	MOVWF      _digit_select+0
	GOTO       L_interrupt18
L_interrupt21:
	MOVLW      10
	MOVWF      R4+0
	MOVF       _south_timer+0, 0
	MOVWF      R0+0
	CALL       _Div_8X8_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      PORTB+0
	BSF        RC2_bit+0, BitPos(RC2_bit+0)
	MOVLW      3
	MOVWF      _digit_select+0
	GOTO       L_interrupt18
L_interrupt22:
	MOVLW      10
	MOVWF      R4+0
	MOVF       _south_timer+0, 0
	MOVWF      R0+0
	CALL       _Div_8X8_U+0
	MOVF       R0+0, 0
	MOVWF      PORTB+0
	BSF        RC3_bit+0, BitPos(RC3_bit+0)
	CLRF       _digit_select+0
	GOTO       L_interrupt18
L_interrupt17:
	MOVF       _digit_select+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt19
	MOVF       _digit_select+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt20
	MOVF       _digit_select+0, 0
	XORLW      2
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt21
	MOVF       _digit_select+0, 0
	XORLW      3
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt22
L_interrupt18:
	CLRF       R1+0
	BTFSC      RE0_bit+0, BitPos(RE0_bit+0)
	INCF       R1+0, 1
	MOVF       R1+0, 0
	XORWF      _prev_man_auto+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt23
	MOVLW      0
	BTFSC      RE0_bit+0, BitPos(RE0_bit+0)
	MOVLW      1
	MOVWF      _prev_man_auto+0
	BTFSS      RE0_bit+0, BitPos(RE0_bit+0)
	GOTO       L_interrupt24
	MOVLW      1
	MOVWF      _exiting_manual+0
	MOVF       _manual_state+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt25
	MOVLW      1
	MOVWF      _manual_state+0
	MOVLW      3
	MOVWF      _west_timer+0
	GOTO       L_interrupt26
L_interrupt25:
	MOVF       _manual_state+0, 0
	XORLW      2
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt27
	MOVLW      3
	MOVWF      _manual_state+0
	MOVLW      3
	MOVWF      _south_timer+0
L_interrupt27:
L_interrupt26:
	GOTO       L_interrupt28
L_interrupt24:
	CLRF       _exiting_manual+0
	BTFSC      RE1_bit+0, BitPos(RE1_bit+0)
	GOTO       L_interrupt29
	MOVLW      2
	MOVWF      _manual_state+0
	GOTO       L_interrupt30
L_interrupt29:
	CLRF       _manual_state+0
L_interrupt30:
L_interrupt28:
L_interrupt23:
	BTFSC      RE0_bit+0, BitPos(RE0_bit+0)
	GOTO       L_interrupt31
	MOVF       _manual_state+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt34
	BTFSC      RE1_bit+0, BitPos(RE1_bit+0)
	GOTO       L_interrupt34
L__interrupt74:
	MOVLW      1
	MOVWF      _manual_state+0
	MOVLW      3
	MOVWF      _west_timer+0
	GOTO       L_interrupt35
L_interrupt34:
	MOVF       _manual_state+0, 0
	XORLW      2
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt38
	BTFSS      RE1_bit+0, BitPos(RE1_bit+0)
	GOTO       L_interrupt38
L__interrupt73:
	MOVLW      3
	MOVWF      _manual_state+0
	MOVLW      3
	MOVWF      _south_timer+0
L_interrupt38:
L_interrupt35:
L_interrupt31:
	INCF       _isr_counter+0, 1
	BTFSC      STATUS+0, 2
	INCF       _isr_counter+1, 1
	MOVLW      0
	SUBWF      _isr_counter+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt78
	MOVLW      250
	SUBWF      _isr_counter+0, 0
L__interrupt78:
	BTFSS      STATUS+0, 0
	GOTO       L_interrupt39
	CLRF       _isr_counter+0
	CLRF       _isr_counter+1
	BTFSS      RE0_bit+0, BitPos(RE0_bit+0)
	GOTO       L_interrupt42
	MOVF       _exiting_manual+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt42
L__interrupt72:
	MOVF       _west_timer+0, 0
	SUBLW      0
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt43
	DECF       _west_timer+0, 1
L_interrupt43:
	MOVF       _south_timer+0, 0
	SUBLW      0
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt44
	DECF       _south_timer+0, 1
L_interrupt44:
	GOTO       L_interrupt45
L_interrupt47:
	MOVF       _west_timer+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt48
	MOVLW      1
	MOVWF      _state+0
	MOVLW      3
	MOVWF      _west_timer+0
L_interrupt48:
	GOTO       L_interrupt46
L_interrupt49:
	MOVF       _west_timer+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt50
	MOVLW      2
	MOVWF      _state+0
	MOVLW      15
	MOVWF      _west_timer+0
	MOVLW      12
	MOVWF      _south_timer+0
L_interrupt50:
	GOTO       L_interrupt46
L_interrupt51:
	MOVF       _south_timer+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt52
	MOVLW      3
	MOVWF      _state+0
	MOVLW      3
	MOVWF      _south_timer+0
L_interrupt52:
	GOTO       L_interrupt46
L_interrupt53:
	MOVF       _south_timer+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt54
	CLRF       _state+0
	MOVLW      20
	MOVWF      _west_timer+0
	MOVLW      23
	MOVWF      _south_timer+0
L_interrupt54:
	GOTO       L_interrupt46
L_interrupt45:
	MOVF       _state+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt47
	MOVF       _state+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt49
	MOVF       _state+0, 0
	XORLW      2
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt51
	MOVF       _state+0, 0
	XORLW      3
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt53
L_interrupt46:
	GOTO       L_interrupt55
L_interrupt42:
	MOVF       _manual_state+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt56
	MOVF       _west_timer+0, 0
	SUBLW      0
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt57
	DECF       _west_timer+0, 1
L_interrupt57:
	MOVF       _west_timer+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt58
	MOVF       _exiting_manual+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt59
	CLRF       _exiting_manual+0
	MOVLW      2
	MOVWF      _state+0
	MOVLW      15
	MOVWF      _west_timer+0
	MOVLW      12
	MOVWF      _south_timer+0
	GOTO       L_interrupt60
L_interrupt59:
	MOVLW      2
	MOVWF      _manual_state+0
L_interrupt60:
L_interrupt58:
	GOTO       L_interrupt61
L_interrupt56:
	MOVF       _manual_state+0, 0
	XORLW      3
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt62
	MOVF       _south_timer+0, 0
	SUBLW      0
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt63
	DECF       _south_timer+0, 1
L_interrupt63:
	MOVF       _south_timer+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt64
	MOVF       _exiting_manual+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt65
	CLRF       _exiting_manual+0
	CLRF       _state+0
	MOVLW      20
	MOVWF      _west_timer+0
	MOVLW      23
	MOVWF      _south_timer+0
	GOTO       L_interrupt66
L_interrupt65:
	CLRF       _manual_state+0
L_interrupt66:
L_interrupt64:
L_interrupt62:
L_interrupt61:
L_interrupt55:
L_interrupt39:
L_interrupt16:
L_end_interrupt:
L__interrupt77:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_main:

	CLRF       TRISB+0
	CLRF       TRISC+0
	CLRF       TRISD+0
	MOVLW      3
	MOVWF      TRISE+0
	MOVLW      6
	MOVWF      ADCON1+0
	CLRF       PORTB+0
	CLRF       PORTC+0
	CLRF       PORTD+0
	BTFSC      RE1_bit+0, BitPos(RE1_bit+0)
	GOTO       L_main67
	MOVLW      2
	MOVWF      _manual_state+0
	GOTO       L_main68
L_main67:
	CLRF       _manual_state+0
L_main68:
	CALL       _update_traffic_lights+0
	MOVLW      131
	MOVWF      OPTION_REG+0
	MOVLW      6
	MOVWF      TMR0+0
	BSF        TMR0IE_bit+0, BitPos(TMR0IE_bit+0)
	BSF        GIE_bit+0, BitPos(GIE_bit+0)
L_main69:
	CALL       _update_traffic_lights+0
	GOTO       L_main69
L_end_main:
	GOTO       $+0
; end of _main
