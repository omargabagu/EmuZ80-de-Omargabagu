#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdint.h> //Para tipos como unit8_t

// Variables globales 
	uint8_t A, B, C, D, E, H, L, F, I, R;
	uint16_t SP, PC, IX, IY;
	bool S, Z, Hf,N, PV, NCf;
	bool stop=0;
	int totalIns = 0;



	uint8_t mem [65536];//del 0 al 65,535 (0-1111111111111111)
	
int loadProgram(uint8_t dirInicio, char *fileName){
    char line[44];
    char ins[20];    
    char ignore[7];
    int totalIns = 0;
    int numInstructions;
    int currentDir = dirInicio;

    FILE *PROGRAM = fopen(fileName, "r");
    if (PROGRAM == NULL)
    {
        printf("FILE NOT FOUND!!!\n");
        return -1;
    }

    while (!feof(PROGRAM))
    {
        fgetc(PROGRAM);
        fscanf(PROGRAM, "%2x%6c", &numInstructions, ignore);
        totalIns += numInstructions;
        while (numInstructions != 0)
        {
            fscanf(PROGRAM, "%2x", &mem[currentDir]);
            ++ currentDir;
            -- numInstructions;
        }
        fscanf(PROGRAM, "%s", ignore);
        fgetc(PROGRAM);
        fgetc(PROGRAM);
    }
    
    fclose(PROGRAM);
}

void push (int8_t data)
{
    if (SP <= 0)
    {
        //fprintf(stderr, "Limite de memoria alcanzado\n");
        return ;
    }
    SP --;
    mem[SP] = data;
}

int8_t pop ()
{
    if (SP >= 65535)
    {
        //fprintf(stderr, "Limite de memoria alcanzado\n");
    }
    
    int8_t data = mem[SP];
    SP ++;
    return data;
}

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
		*first=(data>>8);
		*last=data;
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
uint8_t getFirst(uint16_t data){
	return data>>8;
}
//el fetch de toda la vida
uint8_t fetch(){
	uint8_t data = mem[PC];
	PC++;
	return data;
}
void setAddFlags(uint8_t res){
	if(res<0){S=1;}else {S=0;}
	if(res==0){Z=1;}else {Z=0;}
	//Hf PENDIENTE
	//PV PENDIENTE
	//C PENDIENTE
	N=false;
	
}
void setDecFlags(uint8_t res){
	if(res<0){S=1;}else {S=0;}
	if(res==0){Z=1;}else {Z=0;}
	//Hf PENDIENTE
	//PV PENDIENTE
	N=true;
}
//decodificar y ejecutar, retorna los tick del relog :D 
unsigned int decodeyexecute(const uint8_t opcode){
	unsigned int ticks;
	uint8_t n;
	uint8_t subopcode;
	uint16_t nn;
	int d;
	switch (opcode){
		case 	0x00	: //	NOP
						ticks=4;	break;
		case 	0x76	: //	HALT
			stop=1;				
				break;
//----------------------------------------------
//				GRUPO DE CARGA 8 BITS
//----------------------------------------------
//		LD r, r´
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
//		LD r, n 
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
//		LD r,(HL) 
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
//		GRUPO IX 
//-------------------------------------------------------
		case	0xDD	:
			subopcode=fetch();
			switch (subopcode){
//--------------------------CARGA 8 BITS IX -------------
			//  LD r,(IX+d) 				
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
				case 	0x6E	: //	LD L, (IX+d)
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
					default:
					printf("Instruction with %2x %2x opcode not suported\n",opcode,subopcode);
					stop=1;
//--------------------------CARGA 16 BITS IX--------------
				case 	0x21	: //	LD IX, nn
					n=fetch();
					IX=getFrom2Reg(n,fetch());	ticks=14;	break;
				case	0x2A	: //	LD IX, (nn)
					n=fetch();
					nn=getFrom2Reg(n,fetch()); 
					n=fetch();
					IX=getFrom2Reg	(mem[getFrom2Reg(n,fetch())],	mem[nn]);	
												ticks=20;	break;
				case 	0x22	: //	LD (nn), IX
					n=fetch();
					mem[getFrom2Reg(n,fetch())]=IX;	n=fetch();	
					mem[getFrom2Reg(n,fetch())]=getFirst(IX);		
												ticks=16;	break;
				case	0xF9	: //	LD SP, IX
					SP=IX;						ticks=20;	break;
				case	0x86	: //	ADD A, (IX+d)
					A=A+mem[IX+fetch()];
					setAddFlags(A);				ticks=19;	break;
			}
//		GRUPO IY
//-------------------------------------------------------
		case	0xFD	:
			subopcode=fetch();
			switch (subopcode){
//--------------------------CARGA 8 BITS IY -------------
//				LD r, (IY+d)
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
//				LD (IY+d), r
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
//-------------------------CARGA DE 16 BITS IY ----------------------
				case 	0x21	: //	LD IY, nn
					n=fetch();
					IY=getFrom2Reg(n,fetch());	ticks=14;	break;
				case	0x2A	: //	LD IY, (nn)
					n=fetch();
					nn=getFrom2Reg(n,fetch()); 
					n=fetch();
					IY=getFrom2Reg	(mem[getFrom2Reg(n,fetch())],	mem[nn]);	
												ticks=20;	break;
				case	0xF9	: //	LD SP, IY
					SP=IY;						ticks=20;	break;
//-------------------------SGRUPO ARITMETICO 8 BITS -------------------
				case	0x86	: //	ADD A, (IY+d)
					A=A+mem[IY+fetch()];
					setAddFlags(A);				ticks=19;	break;
				default:
					printf("Instruction with %2x %2x opcode not suported\n",opcode,subopcode);
					stop=1;
			}
//		LD (HL), r
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
			A=mem[getFrom2Reg(fetch(),n)];	ticks=13;	break;
		case	0x02	://		LD (BC), A
			mem[getFrom2Reg(B,C)]=A;			ticks=7;	break;
		case	0x12	://		LD (DE), A
			mem[getFrom2Reg(D,E)]=A;			ticks=7;	break;
		case	0x32	://		LD (nn), A
			n=fetch();
			mem[getFrom2Reg(n,fetch())]=A;	ticks=13;	break;
//		GRUPO 0xED
//--------------------------------------------------------------
		case 	0xED	:
			subopcode=fetch();
			switch (opcode){
//--------------------PENDIENTE AFECTAN BANDERAS (NO IMPLEMENTADO pag 108-110)------------------------

				case	0x57	: //	LD A, I
					A=I;					ticks=9;	break;
				case	0x5F	: //	LD A, R
					A=R;					ticks=9;	break;
					
					//NO HAY BANDERAS INVOLUCRADAS
				case	0x47	: //	LD I, A
					I=A;					ticks=9;	break;
				case	0x4F	: //	LD R, A
					R=A;					ticks=9;	break;
					
					
					//CARGA DE 16 BITS 
					
					
//------------------------LD dd, (nn)		ddh <- (nn + 1)		ddl <- (nn)-----------------------------
				case 	0x4B	: //	LD BC, (nn)
					n=fetch();nn=getFrom2Reg(n,fetch());
					C=mem[nn];
					n=fetch();nn=getFrom2Reg(n,fetch());
					B=mem[nn];					ticks=20;	break;
				case	0x5B	: //	LD DE, (nn)
					n=fetch();nn=getFrom2Reg(n,fetch());
					E=mem[nn];
					n=fetch();nn=getFrom2Reg(n,fetch());
					D=mem[nn];					ticks=20;	break;
				case	0x6B	: //	LD HL, (nn)
					n=fetch();nn=getFrom2Reg(n,fetch());
					H=mem[nn];
					n=fetch();nn=getFrom2Reg(n,fetch());
					L=mem[nn];					ticks=20;	break;
				case 	0x7B	: //	LD SP, (nn)
					n=fetch();
					nn=getFrom2Reg(n,fetch()); 
					n=fetch();
					SP=getFrom2Reg	(mem[getFrom2Reg(n,fetch())],	mem[nn]);	
												ticks=20;	break;
					
//-------------------------LD (nn), dd		(nn + 1) <- ddh, (nn) <- ddl
				case	0x43	: //	LD (nn), BC
					n=fetch();
					mem[getFrom2Reg(n,fetch())]=C;	n=fetch();	
					mem[getFrom2Reg(n,fetch())]=B;		ticks=16;	break;
				case	0x53	: //	LD (nn), DE
					n=fetch();
					mem[getFrom2Reg(n,fetch())]=E;	n=fetch();	
					mem[getFrom2Reg(n,fetch())]=D;		ticks=16;	break;
				case	0x63	: //	LD (nn), HL
					n=fetch();
					mem[getFrom2Reg(n,fetch())]=L;	n=fetch();	
					mem[getFrom2Reg(n,fetch())]=H;		ticks=16;	break;
				case	0x73	: //	LD (nn), SP
					n=fetch();
					mem[getFrom2Reg(n,fetch())]=SP;	n=fetch();	
					mem[getFrom2Reg(n,fetch())]=getFirst(SP);	
														ticks=16;	break;
				default:
					printf("Instruction with %2x %2x opcode not suported\n",opcode,subopcode);
					stop=1;

			}
//----------------------------------------------
//				GRUPO DE CARGA 16 BITS
//----------------------------------------------
//					LD dd,nn
		case	0x01	: //	LD BC, nn
			n=fetch();
			B=n; C=fetch();						ticks=9;	break;
		case	0x11	: //	LD DE, nn
			n=fetch();
			D=n; E=fetch();						ticks=9;	break;
		case	0x21	: //	LD HL, nn
			n=fetch();
			H=n;; L=fetch();					ticks=9;	break;
		case	0x31	: //	LD SP, nn
			n=fetch();
			SP=getFrom2Reg(n,fetch());			ticks=9;	break;
		
		case	0x2A	: //	LD HL, (nn)
			n=fetch();
			L=mem[getFrom2Reg(n,fetch())];	n=fetch();
			H=mem[getFrom2Reg(n,fetch())];		ticks=16;	break;
		case	0x22	: //	LD (nn), HL			(nn + 1) <- H, (nn) <- L
			n=fetch();
			mem[getFrom2Reg(n,fetch())]=L;	n=fetch();	
			mem[getFrom2Reg(n,fetch())]=H;		ticks=16;	break;
		case	0xF9	: //	LD SP, HL
			SP=getFrom2Reg(H,L);				ticks=6;	break;
//		PUSH qq
		case	0xC5	: //	PUSH BC
			
												ticks=11;	break;
		case	0xD5	: //	PUSH DE
												ticks=11;	break;
		case	0xE5	: //	PUSH HL
												ticks=11;	break;
		case	0xF5	: //	PUSH AF
												ticks=11;	break;
			
			
		
		
		
		


//----------------------------------------------
//				GRUPO ARITMETICO 8 BITS
//----------------------------------------------
		case 	0x80	: //ADD A,B  
			A=A+B;				
			setAddFlags(A);				
			ticks=4;	break;	   	
		case 	0x81	://ADD A,C 
			A=A+C;				
			setAddFlags(A);				
			ticks=4;	break;    	
		case 	0x82	://ADD A,D
			A=A+D;
			setAddFlags(A);				
			ticks=4;	break;      	
		case 	0x83	://ADD A,E
			A=A+E;
			setAddFlags(A);				
			ticks=4;	break;    	
		case 	0x84	://ADD A,H
			A=A+H;
			setAddFlags(A);				
			ticks=4;	break;     	
		case 	0x85	://ADD A,L    
			A=A+L;
			setAddFlags(A);				
			ticks=4;	break; 
		case 	0x86	://ADD A,(HL)
			A=A+mem[getFrom2Reg(H,L)];
			setAddFlags(A);
			ticks=7;				break;   	
		case 	0x87	://ADD A,A 
			A=A+A;
			setAddFlags(A);				
			ticks=4;	break;  
		case	0xC6	://ADD A,n
			n=fetch();
			A=A+n;
			setAddFlags(A);				
			ticks=7;	break; 
			
		/*case 	0x88	://ADC A,B 
							break;     	
		case 	0x89	://ADC A,C 
							break;     	
		case 	0x8A	://ADC A,D 
							break;     	
		case 	0x8B	://ADC A,E 
							break;     	
		case 	0x8C	://ADC A,H 
							break;     	
		case 	0x8D	://ADC A,L 
							break;     	
		case 	0x8E	://ADC A,(HL)  	
							break; 
		case 	0x8F	://ADC A,A 
							break;   */
							  	
		case 	0x90	://SUB B   
			A=A-B;
			setAddFlags(A);				
			ticks=4;	break;      	
		case 	0x91	://SUB C   
			A=A-C;
			setAddFlags(A);				
			ticks=4;	break;      	
		case 	0x92	://SUB D   
			A=A-D;
			setAddFlags(A);				
			ticks=4;	break;      	
		case 	0x93	://SUB E   
			A=A-H;
			setAddFlags(A);				
			ticks=4;	break;      	
		case 	0x94	://SUB H     
			A=A-H;
			setAddFlags(A);				
			ticks=4;	break;    	
		case 	0x95	://SUB L   
			A=A-L;
			setAddFlags(A);				
			ticks=4;	break;      	
		case 	0x96	://SUB (HL)
			A=A-mem[getFrom2Reg(H,L)];
			setAddFlags(A);
			ticks=7;		break;     	
		case 	0x97	://SUB A   
			A=A-A;
			setAddFlags(A);				
			ticks=4;	break;
		case	0xD6	: //SUB n 
			A=A-fetch();
			setAddFlags(A);
			ticks=7;		break;      	

//----------------------------------------------
//				GRUPOS DE PROPOSITO GENERAL ARITMETICO Y CONTROL 
//----------------------------------------------

//----------------------------------------------
//				GRUPO ARITMETICO 16 BITS
//----------------------------------------------
		case	0x09	://ADD HL,BC
					nn=getFrom2Reg(H,L); //nn es una variable temporal para guardar valores de 16 bits, en este caso HL
		            nn+=getFrom2Reg(B,C);      
					H=getFirst(nn); L=nn;
					ticks=11;	break;
		case	0x19	://ADD HL,DE
					nn=getFrom2Reg(H,L); //nn es una variable temporal para guardar valores de 16 bits, en este caso HL
		            nn+=getFrom2Reg(D,E);      
					H=getFirst(nn); L=nn;
					ticks=11;	break;
		case	0x29	://ADD HL,HL
					nn=getFrom2Reg(H,L); //nn es una variable temporal para guardar valores de 16 bits, en este caso HL
		            nn+=getFrom2Reg(H,L);      
					H=getFirst(nn); L=nn;
					ticks=11;	break;
		case	0x39	://ADD HL,SP
					nn=getFrom2Reg(H,L); //nn es una variable temporal para guardar valores de 16 bits, en este caso HL
		            nn+=SP;      
					H=getFirst(nn); L=nn;
					ticks=11;	break;
		case	0x05	://DEC B
					B--;	setDecFlags(B);
					ticks=4;	break;
		case	0x0D	://DEC C
					C--;	setDecFlags(C);
					ticks=4;	break;
		case	0x15	://DEC D
					D--;	setDecFlags(D);
					ticks=4;	break;
		case	0x1D	://DEC E
					E--;	setDecFlags(E);
					ticks=4;	break;
		case	0x25	://DEC H
					H--;	setDecFlags(H);
					ticks=4;	break;
		case	0x2D	://DEC L
					L--;	setDecFlags(L);
					ticks=4;	break;
		case	0x3D	://DEC A
					A--;	setDecFlags(A);
					ticks=4;	break;
		case	0x35	://DEC HL
					nn=getFrom2Reg(H,L);
					nn--;	setDecFlags(nn);
					H=getFirst(H);L=nn;
					ticks=11;	break;
				
//----------------------------------------------
//				GRUPO DE ROTACIÓN Y DESPLAZAMIENTO 		 
//----------------------------------------------

//----------------------------------------------
//				GRUPO BIT SET, RESET Y TEST
//----------------------------------------------

//----------------------------------------------
//				GRUPO DE SALTOS
//----------------------------------------------

		//----------------------------------------------
//				GRUPO DE SALTOS
//----------------------------------------------
		case	0xC3	://JP nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			PC=nn;
			ticks=10;		break;
		case	0xC2	://JP NZ, nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			if(Z==0){
				PC=nn;
			}ticks=10;		break;
		case	0xCA	://JP Z, nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			if(Z==1){
				PC=nn;
			}ticks=10;		break;
		case	0xD2	://JP NC, nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			if(NCf==0){
				PC=nn;
			}ticks=10;		break;
		case	0xDA	://JP C, nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			if(NCf==1){
				PC=nn;
			}ticks=10;		break;
		case	0xE2	://JP PO, nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			if(PV==0){
				PC=nn;
			}ticks=10;		break;
		case	0xEA	://JP PE, nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			if(PV==1){
				PC=nn;
			}ticks=10;		break;
		case	0xF2	://JP P, nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			if(S==0){
				PC=nn;
			}ticks=10;		break;
		case	0xFA	://JP M, nn
			n=fetch();
			nn=getFrom2Reg(fetch(),n);
			if(S==1){
				PC=nn;
			}ticks=10;		break;	
		case	0x18	://JR e
			n=fetch();
			PC=PC+n;
			ticks=12;		break;
		case	0x38	://JR C, e
			n=fetch();
			if(NCf==1){
				PC=PC+n;
				ticks=12;
			}else
				ticks=7;	break;
		case	0x30	://JR NC, e
			n=fetch();
			if(NCf==1){
				PC=PC+n;
				ticks=12;
			}else
				ticks=7;	break;
		case	0x28	://JR Z, e
			n=fetch();
			if(Z==1){
				PC=PC+n;
				ticks=12;
			}else
				ticks=7;	break;
		case	0x20	://JR NZ, e
			n=fetch();
			if(Z==0){
				PC=PC+n;
				ticks=12;
			}else
				ticks=7;	break;
		case	0xE9	://JP (HL)
			PC=mem[getFrom2Reg(H,L)];
			ticks=4;		break;
		case	0x10	://DJNZ, e
			B=B-1;
			n=fetch();
			if(Z==0){
				PC=PC+n;
				ticks=13;
			}else
				ticks=8;	break;
//----------------------------------------------
//				GRUPO DE LLAMADA Y RETORNO 
//----------------------------------------------

//----------------------------------------------
//				GRUPO INPUT Y PUTPUT
//----------------------------------------------
		default:
			printf("Instruction with %2x opcode not suported\n",opcode);
			stop=1;	

	} 
	return ticks;
}

int ascii_to_hex(char c){
	int num = (int) c;
	if(num < 58 && num > 47){
	    return num - 48; 
	}
	if(num < 103 && num > 96){
	    return num - 87;
	}
	return num;
}
#define FILELEN 15
/*
void readFile(){
        FILE *fp = fopen("sample","r");
        unsigned char c1,c2;
        int i=0;
        unsigned char sum,final_hex[FILELEN/2];
        for(i=0;i<FILELEN/2;i++)
        {
                c1 = ascii_to_hex(fgetc(fp));
                c2 = ascii_to_hex(fgetc(fp));
                sum = c1<<4 | c2;
                final_hex[i] = sum;
                printf("%02x ",sum);
        }
        printf("\n");
}*/
void printMem(uint8_t dir){
    uint8_t line = dir / 16;

    printf("\n\t");
    for (int i = 0; i < 16; i++)
    {
        printf(" %02X", i);
    }
    printf("\n\n");
    
    for (int i = line; i < line+16; i++)
    {
        printf("%04X\t", i*16);
        for (int j = 0; j < 16; j++){
        	if (PC==(i*16)+j){
        		printf(">%02X", mem[(i*16)+j]);
			}else{
				printf(" %02X", mem[(i*16)+j]);
			}
            
        }
        printf("\n");
    }
    
}

void printScreen(int memPage,uint8_t opcode){
	// Flags S, Z, Hf,N, PV, NCf;
	printf("---Enter to continue---\n");
	printf("Registers:					Flags:\n");
	printf("A:%i	B:%i	C:%i				Z:",A,B,C);		printf(Z ? "true\n" : "false\n");
	printf("D:%i	E:%i	F:%i				S:",D,E,F);		printf(S ? "true\n" : "false\n");
	printf("H:%i	L:%i	HL:%i				H:",H,L,getFrom2Reg(H,L));printf(Hf ? "true\n" : "false\n");
	printf("I:%i	R:%i	IR:%i				N:",I,R,getFrom2Reg(I,R));printf(N ? "true\n" : "false\n");
	printf("SP:%i		IX:%i				P/V:",SP,IX,PV);	printf(PV ? "true\n" : "false\n");
	printf("PC:%i		IY:%i		Data:%2X		NC:",PC,IY,opcode);		printf(NCf ? "true\n" : "false\n");
	printf("		---Memory---");
	printMem(0);
}
	
int main(){
	/*
	uint16_t data = 31245;	//0111 1010  0000 1101 
	uint8_t n=122;			//0111 1010    
	uint8_t n1=13;			//			 0000 1101
	
	//Probando asignacion independiente 
	H=n;
	L=n1;
	printf("H:");printBB(H);
	printf("L:");printBB(L);
	printf("HL: %i\n",getFrom2Reg(H,L));
	//Porbando asignación con load2Reg()
	
	/*load2Reg(&H,&L,data);
	printf("H:");printBB(H);
	printf("L:");printBB(L);
	printf("HL: %i\n",getFrom2Reg(H,L));
	//Probando getFirst()
	SP=data;
	printf("SP first (S): ");printBB(getFirst(SP));
	printf("HP first (H): ");printBB(getFirst(getFrom2Reg(H,L)));
	*/
	//RUN (ciclo de ejecución)
	
	loadProgram(0, "CONC.HEX");
	printScreen(0,0);
	for (;stop==0;){
		getchar(); 
		system("cls");
		uint8_t opcode = fetch();
		decodeyexecute(opcode);
		printScreen(0,opcode);
		
	}
	//printf("Fin del programa");
	return 0;
}
