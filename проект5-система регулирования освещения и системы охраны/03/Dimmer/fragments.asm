; === ПОДПРОГРАММЫ

; === изменение уровня
увеличить   incf        уровень,F
            goto        $+2
уменьшить   decf        уровень,F
            ; 0 <= уровень <= 10
            movf        уровень,W
            xorlw       .255
            btfsc       STATUS,Z
            incf        уровень,F
            movf        уровень,W
            addlw       .245
            btfsc       STATUS,C
            decf        уровень,F
            btfsc       STATUS,C
            goto        $-5
            откл
            Pause3      .169,.69,.2
            return

; === ожидание перехода через "0"
ZC          btfss       сенсор
            goto        $+4
            btfsc       сенсор      ; выход из "+" полуволны
            goto        $-1
            return
            btfss       сенсор      ; выход из "-" полуволны
            goto        $-1
            return

; === привязка уровня к задержке
задержка    movf        уровень,W
            xorlw       .10
            btfsc       STATUS,Z
            goto        П10         ; max уровень

            movf        уровень,W
            xorlw       .0
            btfsc       STATUS,Z
            goto        П0          ; min уровень

            movf        уровень,W
            xorlw       .1
            btfsc       STATUS,Z
            goto        П1

            movf        уровень,W
            xorlw       .2
            btfsc       STATUS,Z
            goto        П2            

            movf        уровень,W
            xorlw       .3
            btfsc       STATUS,Z
            goto        П3

            movf        уровень,W
            xorlw       .4
            btfsc       STATUS,Z
            goto        П4

            movf        уровень,W
            xorlw       .5
            btfsc       STATUS,Z
            goto        П5

            movf        уровень,W
            xorlw       .6
            btfsc       STATUS,Z
            goto        П6

            movf        уровень,W
            xorlw       .7
            btfsc       STATUS,Z
            goto        П7

            movf        уровень,W
            xorlw       .8
            btfsc       STATUS,Z
            goto        П8

            movf        уровень,W
            xorlw       .9
            btfsc       STATUS,Z
            goto        П9

            return ; страховочный возврат

; === собственно сами задержки
П10         вкл
            рисуем      _Н
            ; далее команда вызывает переполнение стека
            ; но в данном месте это не критично
            goto        цикл ; <- это она

П0          рисуем      _0
            return

П1          Pause2      .21,.10 ; 7000 мкс
            вкл
            рисуем      _1
            return

П2          Pause2      .111,.9 ; 6500 мкс
            вкл
            рисуем      _2
            return

П3          Pause2      .201,.8 ; 6000 мкс
            вкл
            рисуем      _3
            return

П4          Pause2      .35,.8 ; 5500 мкс
            вкл
            рисуем      _4
            return

П5          Pause2      .125,.7 ; 5000 мкс
            вкл
            рисуем      _5
            return

П6          Pause2      .215,.6 ; 4500 мкс
            вкл
            рисуем      _6
            return

П7          Pause2      .48,.6 ; 4000 мкс
            вкл
            рисуем      _7
            return

П8          Pause2      .138,.5 ; 3500 мкс
            вкл
            рисуем      _8
            return

П9          Pause2      .228,.4 ; 3000 мкс
            вкл
            рисуем      _9
            return
