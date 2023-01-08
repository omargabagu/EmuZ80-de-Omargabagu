#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h> //Para tipos como unit8_t
// Variables globales 
	uint8_t A, B, C, D, E, H, L, F, I, R;
	uint16_t SP, PC, IX, IY;
	bool S, Z, Hf, PV, NCf;



	uint8_t mem [65536];//del 0 al 65,535 (0-1111111111111111)

//Imprime Data de 8 bits en binario
void printBB(uint8_t data){
	int idata = data;
    for (int i = 7; i > -1; i--)
        printf("%d", (idata & (1 << i)) >> i );
    putc('\n', stdout);
}
//Imprime Data de 16 bits en binario
void printBB16(uint16_t data){
	int idata = data;
    for (int i = 15; i > -1; i--)
        printf("%d", (idata & (1 << i)) >> i );
    putc('\n', stdout);
}
/*Es para asignar a un par de registro un valor. Ej: load2Reg(&H,&L,1234);
 	first es el primer registro
 	last es el segundo registrp
 	data es el dato que se va a separar y guardar en ambos registros	*/
void load2Reg(uint8_t *first,uint8_t *last,uint16_t data){
	if (data<=256){
		*first=0;
		*last=data;
	}else {
		*first=(data>>8) & 0xFF;
		*last=data & 0xFF;
	}
	
}
/*Es para obtener un dato de 16bits de un par de registros
	ej: PC = getFrom2Reg(H,L)); PC<-HL
 	first es el primer registro
 	last es el segundo registrp		*/
uint16_t getFrom2Reg(uint8_t first,uint8_t last){
	uint16_t tmpFirst=first<<8;
	return tmpFirst | last;
}
//el fetch de toda la vida
uint8_t fetch(){
	uint8_t data = mem[PC];
	PC++;
	return data;
}
//decodificar y ejecutar, retorna los tick del relog :D 
unsigned int decodeyexecute(const uint8_t opcode){
	unsigned int ticks;
	uint8_t n;
	uint8_t subopcode;
	int d;
	switch (opcode){
		case 	0x00	: //	NOP
						ticks=4;	break;
//----------------------------------------------
//				GRUPO DE CARGA 8 BITS
//----------------------------------------------
		case	0x7F	: //	LD A, A
			A=A;		ticks=4;	break;
		case	0x78	: //	LD A, B		
			A=B;		ticks=4;	break;
		case	0x79	: //	LD A, C		
			A=C;		ticks=4;	break;
		case	0x7A	: //	LD A, D		
			A=D;		ticks=4;	break;
		case	0x7B	: //	LD A, E		
			A=E;		ticks=4;	break;
		case	0x7C	: //	LD A, H		
			A=H;		ticks=4;	break;
		case	0x7D	: //	LD A, L		
			A=L;		ticks=4;	break;
		case	0x47	: //	LD B, A		
			B=A;		ticks=4;	break;
		case	0x40	: //	LD B, B		
			B=B;		ticks=4;	break;
		case	0x41	: //	LD B, C		
			B=C;		ticks=4;	break;
		case	0x42	: //	LD B, D		
			B=D;		ticks=4;	break;
		case	0x43	: //	LD B, E		
			B=E;		ticks=4;	break;
		case	0x44	: //	LD B, H		
			B=H;		ticks=4;	break;
		case	0x45	: //	LD B, L		
			B=L;		ticks=4;	break;
		case	0x4F	: //	LD C, A		
			C=A;		ticks=4;	break;
		case	0x48	: //	LD C, B		
			C=B;		ticks=4;	break;
		case	0x49	: //	LD C, C		
			C=C;		ticks=4;	break;
		case	0x4A	: //	LD C, D		
			C=D;		ticks=4;	break;
		case	0x4B	: //	LD C, E		
			C=E;		ticks=4;	break;
		case	0x4C	: //	LD C, H		
			C=H;		ticks=4;	break;
		case	0x4D	: //	LD C, L		
			C=L;		ticks=4;	break;
		case	0x57	: //	LD D, A		
			D=A;		ticks=4;	break;
		case	0x50	: //	LD D, B		
			D=B;		ticks=4;	break;
		case	0x51	: //	LD D, C		
			D=C;		ticks=4;	break;
		case	0x52	: //	LD D, D		
			D=D;		ticks=4;	break;
		case	0x53	: //	LD D, E		
			D=E;		ticks=4;	break;
		case	0x54	: //	LD D, H		
			D=H;		ticks=4;	break;
		case	0x55	: //	LD D, L		
			D=L;		ticks=4;	break;
		case	0x5F	: //	LD E, A		
			E=A;		ticks=4;	break;
		case	0x58	: //	LD E, B		
			E=B;		ticks=4;	break;
		case	0x59	: //	LD E, C		
			E=C;		ticks=4;	break;
		case	0x5A	: //	LD E, D		
			E=D;		ticks=4;	break;
		case	0x5B	: //	LD E, E		
			E=E;		ticks=4;	break;
		case	0x5C	: //	LD E, H		
			E=H;		ticks=4;	break;
		case	0x5D	: //	LD E, L		
			E=L;		ticks=4;	break;
		case	0x67	: //	LD H, A		
			H=A;		ticks=4;	break;
		case	0x60	: //	LD H, B		
			H=B;		ticks=4;	break;
		case	0x61	: //	LD H, C		
			H=C;		ticks=4;	break;
		case	0x62	: //	LD H, D		
			H=D;		ticks=4;	break;
		case	0x63	: //	LD H, E		
			H=E;		ticks=4;	break;
		case	0x64	: //	LD H, H		
			H=H;		ticks=4;	break;
		case	0x65	: //	LD H, L		
			H=L;		ticks=4;	break;
		case	0x6F	: //	LD L, A		
			L=A;		ticks=4;	break;
		case	0x68	: //	LD L, B		
			L=B;		ticks=4;	break;
		case	0x69	: //	LD L, C		
			L=C;		ticks=4;	break;
		case	0x6A	: //	LD L, D		
			L=D;		ticks=4;	break;
		case	0x6B	: //	LD L, E		
			L=E;		ticks=4;	break;
		case	0x6C	: //	LD L, H		
			L=H;		ticks=4;	break;
		case	0x6D	: //	LD L, L		
			L=L;		ticks=4;	break;
//					LD r, n 
		case	0x3E	: //	LD A, n		
			n = fetch();
			A=n;		ticks=7;	break;
		case	0x06	: //	LD B, n			
			n = fetch();
			B=n;		ticks=7;	break;
		case	0x0E	: //	LD C, n			
			n = fetch();
			C=n;		ticks=7;	break;
		case	0x16	: //	LD D, n			
			n = fetch();
			D=n;		ticks=7;	break;
		case	0x1E	: //	LD E, n			
			n = fetch();
			E=n;		ticks=7;	break;
		case	0x26	: //	LD H, n			
			n = fetch();
			H=n;		ticks=7;	break;
		case	0x2E	: //	LD L, n			
			n = fetch();
			L=n;		ticks=7;	break;
//					LD r,(HL) 
		case	0x7E	: //	LD A, (HL)	
			A=mem[getFrom2Reg(H,L)];	ticks=7;	break;
		case	0x46	: //	LD B, (HL)		
			B=mem[getFrom2Reg(H,L)];	ticks=7;	break;
		case	0x4E	: //	LD C, (HL)		
			C=mem[getFrom2Reg(H,L)];	ticks=7;	break;
		case	0x56	: //	LD D, (HL)		
			D=mem[getFrom2Reg(H,L)];	ticks=7;	break;
		case	0x5E	: //	LD E, (HL)		
			E=mem[getFrom2Reg(H,L)];	ticks=7;	break;
		case	0x66	: //	LD H, (HL)		
			H=mem[getFrom2Reg(H,L)];	ticks=7;	break;
		case	0x6E	: //	LD L, (HL)		
			L=mem[getFrom2Reg(H,L)];	ticks=7;	break;
		case	0xDD	:
			subopcode=fetch();
			switch (subopcode){
//					LD r,(IX+d) 				
				case 	0x7E	: //	LD A, (IX+d)
					A=mem[IX+fetch()];	ticks=19;	break;
				case 	0x46	: //	LD B, (IX+d)
					B=mem[IX+fetch()];	ticks=19;	break;
				case 	0x4E	: //	LD C, (IX+d)
					C=mem[IX+fetch()];	ticks=19;	break;
				case 	0x56	: //	LD D, (IX+d)
					D=mem[IX+fetch()];	ticks=19;	break;
				case 	0x5E	: //	LD E, (IX+d)
					E=mem[IX+fetch()];	ticks=19;	break;
				case	0x66	: //	LD H, (IX+d)
					H=mem[IX+fetch()];	ticks=19;	break;
				case 	0x7D	: //	LD L, (IX+d)
					L=mem[IX+fetch()];	ticks=19;	break;
//					LD (IX+d), r
				case	0x77	: //	LD (IX+d), A
					mem[IX+fetch()]=A;	ticks=19;	break;
				case	0x70	: //	LD (IX+d), B
					mem[IX+fetch()]=B;	ticks=19;	break;
				case	0x71	: //	LD (IX+d), C
					mem[IX+fetch()]=C;	ticks=19;	break;
				case	0x72	: //	LD (IX+d), D
					mem[IX+fetch()]=D;	ticks=19;	break;
				case	0x73	: //	LD (IX+d), E
					mem[IX+fetch()]=E;	ticks=19;	break;
				case	0x74	: //	LD (IX+d), H
					mem[IX+fetch()]=H;	ticks=19;	break;	
				case	0x75	: //	LD (IX+d), L
					mem[IX+fetch()]=L;	ticks=19;	break;
					
				case	0x36	: //	LD (IX+d), n
					d=fetch();
					mem[IX+d]=fetch();	ticks=19;	break;	
			}
//					LD r, (IY+d)
		case	0xFD	:
			subopcode=fetch();
			switch (subopcode){
				case 	0x7E	: //	LD A, (IY+d)
					A=mem[IY+fetch()];		break;
				case 	0x46	: //	LD B, (IY+d)
					B=mem[IY+fetch()];		break;
				case 	0x4E	: //	LD C, (IY+d)
					C=mem[IY+fetch()];		break;
				case 	0x56	: //	LD D, (IY+d)
					D=mem[IY+fetch()];		break;
				case 	0x5E	: //	LD E, (IY+d)
					E=mem[IY+fetch()];		break;
				case	0x66	: //	LD H, (IY+d)
					H=mem[IY+fetch()];		break;
				case 	0x7D	: //	LD L, (IY+d)
					L=mem[IY+fetch()];		break;
//					LD (IY+d), r
				case	0x77	: //	LD (IY+d), A
					mem[IY+fetch()]=A;	ticks=19;	break;
				case	0x70	: //	LD (IY+d), B
					mem[IY+fetch()]=B;	ticks=19;	break;
				case	0x71	: //	LD (IY+d), C
					mem[IY+fetch()]=C;	ticks=19;	break;
				case	0x72	: //	LD (IY+d), D
					mem[IY+fetch()]=D;	ticks=19;	break;
				case	0x73	: //	LD (IY+d), E
					mem[IY+fetch()]=E;	ticks=19;	break;
				case	0x74	: //	LD (IY+d), H
					mem[IY+fetch()]=H;	ticks=19;	break;
				case	0x75	: //	LD (IY+d), L
					mem[IY+fetch()]=L;	ticks=19;	break;
					
				case	0x36	: //	LD (IY+d), n
					d=fetch();
					mem[IY+d]=fetch();		break;
			}
//					LD (HL), r
		case	0x77	: //	LD (HL), A
			mem[getFrom2Reg(H,L)]=A;		ticks=7;	break;
		case	0x70	: //	LD (HL), B
			mem[getFrom2Reg(H,L)]=B;		ticks=7;	break;
		case	0x71	: //	LD (HL), C
			mem[getFrom2Reg(H,L)]=C;		ticks=7;	break;
		case	0x72	: //	LD (HL), D
			mem[getFrom2Reg(H,L)]=D;		ticks=7;	break;
		case	0x73	: //	LD (HL), E
			mem[getFrom2Reg(H,L)]=E;		ticks=7;	break;
		case	0x74	: //	LD (HL), H
			mem[getFrom2Reg(H,L)]=H;		ticks=7;	break;
		case	0x75	: //	LD (HL), L
			mem[getFrom2Reg(H,L)]=L;		ticks=7;	break;
		
		case 	0x36	: // 	LD (HL), n
			n=fetch(); 
			mem[getFrom2Reg(H,L)]=d;		ticks=10;	break;
		case	0x0A	://		LD A, (BC)
			A=mem[getFrom2Reg(B,C)];		ticks=7;	break;
		case	0x1A	://		LD A, (DE)
			A=mem[getFrom2Reg(D,E)];		ticks=7;	break;
		case	0x3A	://		LD A, (nn)
			n=fetch();
			A=mem[getFrom2Reg(n,fetch())];	ticks=13;	break;
		case	0x02	://		LD (BC), A
			mem[getFrom2Reg(B,C)]=A;			ticks=7;	break;
		case	0x12	://		LD (DE), A
			mem[getFrom2Reg(D,E)]=A;			ticks=7;	break;
		case	0x32	://		LD (nn), A
			n=fetch();
			mem[getFrom2Reg(n,fetch())]=A;	ticks=13;	break;
		case 	0xED	:
			subopcode=fetch();
			switch (opcode){
//--------------------AFECTAN BANDERAS (NO IMPLEMENTADO pag 108-110)------------------------

				case	0x57	: //	LD A, I
					A=I;					ticks=9;	break;
				case	0x5F	: //	LD A, R
					A=R;					ticks=9;	break;
				case	0x47	: //	LD I, A
					I=A;					ticks=9;	break;
			}
			
	} 
	return ticks;
}

	
int main(){
	
	load2Reg(&H,&L,1234);
	printf("H:");printBB(H);
	printf("L:");printBB(L);
	printf("HL: %i",getFrom2Reg(H,L));
	
	//RUN (ciclo de ejecución)
	/*
	for (;;){
		uint8_t upcode = fetch();
		decodeyexecute(upcode);
	}*/
	return 0;
}
