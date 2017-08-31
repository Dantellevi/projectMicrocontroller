; === ���� ���������

#define     ��1              PORTA,0  ; ������ 1
#define     ��2              PORTA,1  ; ������ 2

#define     ������           PORTA,2  ; Zero Cross

#define     ���         bcf  PORTA,3  ; ���  �����
#define     ����        bsf  PORTA,3  ; ���� �����

#define     _. .1   ; RB0
#define     _C .2   ; RB1
#define     _D .4   ; RB2
#define     _E .8   ; RB3
#define     _B .16  ; RB4
#define     _A .32  ; RB5
#define     _F .64  ; RB6
#define     _G .128 ; RB7

; ���� ��������� � ����� ������, �� �����
; ����� ������ �� 255, ��������, ��� 
; ������� "1" �������� 255-(_B+_C)
#define     _0 addlw (_A+_B+_C+_D+_E+_F)
#define     _1 addlw (_B+_C)
#define     _2 addlw (_A+_B+_G+_E+_D)
#define     _3 addlw (_A+_B+_G+_C+_D)
#define     _4 addlw (_F+_G+_B+_C)
#define     _5 addlw (_A+_F+_G+_C+_D)
#define     _6 addlw (_A+_F+_G+_C+_D+_E)
#define     _7 addlw (_A+_B+_C)
#define     _8 addlw (_A+_B+_C+_D+_E+_F+_G)
#define     _9 addlw (_A+_B+_C+_D+_F+_G)
#define     _� addlw (_B+_C+_E+_F+_G)

; � ����� ������ �� ��������� �� ���������
������      macro xxx
            clrw
            xxx
            movwf PORTB
            endm
