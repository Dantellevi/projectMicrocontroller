; "��������� �������� ���������
; � �������� ���������� � ��������� �����������"
; �� ������� "�������� ���� ��-����������� 2008"

            #include    P16F628A.INC
            __CONFIG    _INTRC_OSC_NOCLKOUT & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _MCLRE_ON & _LVP_OFF & _DATA_CP_OFF & _CP_OFF

            ;#include    P16F84A.INC
            ;__CONFIG    _HS_OSC & _WDT_OFF & _PWRTE_ON & _CP_OFF

            cblock      20h
Reg:3
�������
            endc

            #include    pause.mac
            #include    alias.asm

; === ���������� ����������������
            bsf         STATUS,RP0  ; � ���� 1 
            movlw       b'10111'
            movwf       TRISA
            clrf        TRISB
            bcf         STATUS,RP0  ; � ���� 0
            clrf        PORTB
            movlw       b'11111111' ; ����������
            movwf       CMCON       ; ������������
            clrf        INTCON      ; ��� pic16f628a

; === ������
            clrf        �������
����        ; ����� ������
            btfss       ��1
            call        ���������
            btfss       ��2
            call        ���������
            call        ��������
            ����
            call        ZC ; Zero-Cross
            goto        ����

            #include    fragments.asm ; ������������

            end
