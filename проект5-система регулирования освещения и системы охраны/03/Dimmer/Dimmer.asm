; "Регулятор мощности паяльника
; с цифровой индикацией и кнопочным управлением"
; на конкурс "Поздравь Кота по-человечески 2008"

            #include    P16F628A.INC
            __CONFIG    _INTRC_OSC_NOCLKOUT & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _MCLRE_ON & _LVP_OFF & _DATA_CP_OFF & _CP_OFF

            ;#include    P16F84A.INC
            ;__CONFIG    _HS_OSC & _WDT_OFF & _PWRTE_ON & _CP_OFF

            cblock      20h
Reg:3
уровень
            endc

            #include    pause.mac
            #include    alias.asm

; === подготовка микроконтроллера
            bsf         STATUS,RP0  ; в Банк 1 
            movlw       b'10111'
            movwf       TRISA
            clrf        TRISB
            bcf         STATUS,RP0  ; в Банк 0
            clrf        PORTB
            movlw       b'11111111' ; отключение
            movwf       CMCON       ; компараторов
            clrf        INTCON      ; для pic16f628a

; === работа
            clrf        уровень
цикл        ; опрос кнопок
            btfss       кн1
            call        увеличить
            btfss       кн2
            call        уменьшить
            call        задержка
            откл
            call        ZC ; Zero-Cross
            goto        цикл

            #include    fragments.asm ; подпрограммы

            end
