; === ������������

; === ��������� ������
���������   incf        �������,F
            goto        $+2
���������   decf        �������,F
            ; 0 <= ������� <= 10
            movf        �������,W
            xorlw       .255
            btfsc       STATUS,Z
            incf        �������,F
            movf        �������,W
            addlw       .245
            btfsc       STATUS,C
            decf        �������,F
            btfsc       STATUS,C
            goto        $-5
            ����
            Pause3      .169,.69,.2
            return

; === �������� �������� ����� "0"
ZC          btfss       ������
            goto        $+4
            btfsc       ������      ; ����� �� "+" ���������
            goto        $-1
            return
            btfss       ������      ; ����� �� "-" ���������
            goto        $-1
            return

; === �������� ������ � ��������
��������    movf        �������,W
            xorlw       .10
            btfsc       STATUS,Z
            goto        �10         ; max �������

            movf        �������,W
            xorlw       .0
            btfsc       STATUS,Z
            goto        �0          ; min �������

            movf        �������,W
            xorlw       .1
            btfsc       STATUS,Z
            goto        �1

            movf        �������,W
            xorlw       .2
            btfsc       STATUS,Z
            goto        �2            

            movf        �������,W
            xorlw       .3
            btfsc       STATUS,Z
            goto        �3

            movf        �������,W
            xorlw       .4
            btfsc       STATUS,Z
            goto        �4

            movf        �������,W
            xorlw       .5
            btfsc       STATUS,Z
            goto        �5

            movf        �������,W
            xorlw       .6
            btfsc       STATUS,Z
            goto        �6

            movf        �������,W
            xorlw       .7
            btfsc       STATUS,Z
            goto        �7

            movf        �������,W
            xorlw       .8
            btfsc       STATUS,Z
            goto        �8

            movf        �������,W
            xorlw       .9
            btfsc       STATUS,Z
            goto        �9

            return ; ������������ �������

; === ���������� ���� ��������
�10         ���
            ������      _�
            ; ����� ������� �������� ������������ �����
            ; �� � ������ ����� ��� �� ��������
            goto        ���� ; <- ��� ���

�0          ������      _0
            return

�1          Pause2      .21,.10 ; 7000 ���
            ���
            ������      _1
            return

�2          Pause2      .111,.9 ; 6500 ���
            ���
            ������      _2
            return

�3          Pause2      .201,.8 ; 6000 ���
            ���
            ������      _3
            return

�4          Pause2      .35,.8 ; 5500 ���
            ���
            ������      _4
            return

�5          Pause2      .125,.7 ; 5000 ���
            ���
            ������      _5
            return

�6          Pause2      .215,.6 ; 4500 ���
            ���
            ������      _6
            return

�7          Pause2      .48,.6 ; 4000 ���
            ���
            ������      _7
            return

�8          Pause2      .138,.5 ; 3500 ���
            ���
            ������      _8
            return

�9          Pause2      .228,.4 ; 3000 ���
            ���
            ������      _9
            return
