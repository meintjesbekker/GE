!///////////////////////////////////////////////////////////////////////
!																		
!	HEADTIME															
!																		
!	Read stress periods and time steps.
!
!	NAME	: path and filename to read from	
!	NOTIMES : number of times
!	PERIODS	: listing of all stress perionds from start to end
!	STEPS	: listing of all time steps from start to end
!	LAYERS	: listing of all layers from start to end
!	NX		: number of columns
!	NY		: number of rows
!	NLAY	: number of layers
!	LAYERN	: layer to get heads from 
!	IERR	: error if eqaul to 1
!
!	KSTP	: time step read from file
!	KPER	: stress period read from file
!	PERTIM	: elapsed time within stress period
!	TOTIM	: total elapsed time since the beginning of simulation
!	TEXT	: drawdown or head
!	NC		: number of columns
!	NR		: number of rows
!	K		: layer number
!																		
!///////////////////////////////////////////////////////////////////////

		SUBROUTINE HEADTIME(NAME, NOTIMES, PERIODS, TSTEPS, LAYERS, NX, NY, NLAY, IERR)
		DLL_EXPORT HEADTIME

		CHARACTER*180 	NAME
		INTEGER 		NOTIMES
		INTEGER			PERIODS(0:NOTIMES-1)
		INTEGER			TSTEPS(0:NOTIMES-1)
		INTEGER			LAYERS(0:NOTIMES-1)
		INTEGER			NX
		INTEGER			NY
		INTEGER			NLAY
		INTEGER			IERR
		
		INTEGER			KSTP
		INTEGER			KPER
		REAL			PERTIM
		REAL  			TOTIM
		CHARACTER*16 	TEXT
		INTEGER			NC
		INTEGER			NR
		INTEGER			K
		
		REAL 			HEAD(0:NX*NY-1)
		
		INTEGER			I

		IERR = 0
		
		OPEN(1, FILE = TRIM(NAME), FORM = 'UNFORMATTED', ERR = 50)

		I = 0

30 		DO NL = 1, NLAY
			READ(1, END = 999) KSTP, KPER, PERTIM, TOTIM, TEXT, NC, NR, K
			READ(1, END = 999) HEAD
			
			PERIODS(I) = KPER
			TSTEPS(I)  = KSTP	
			LAYERS(I)  = K
			
			I = I + 1
		END DO

		GOTO 30       
				
50		IERR = 1

999		NOTIMES	= I
		CLOSE(1)
		END

!///////////////////////////////////////////////////////////////////////
!																		
!	READHEAD															
!																		
!	Read heads.                                   					
!
!	NAME	: path and filename to read from	
!	PER		: stress period	
!	STP		: time step
!	HEAD	: array to contain heads read
!	NX		: number of columns
!	NY		: number of rows
!	NLAY	: number of layers
!	LAYERN	: layer to get heads from 
!	IERR	: error if eqaul to 1
!
!	KSTP	: time step read from file
!	KPER	: stress period read from file
!	PERTIM	: elapsed time within stress period
!	TOTIM	: total elapsed time since the beginning of simulation
!	TEXT	: drawdown or head
!	NC		: number of columns
!	NR		: number of rows
!	K		: layer number
!																					
!///////////////////////////////////////////////////////////////////////

		SUBROUTINE READHEAD(NAME, PER, STP, HEAD, NX, NY, NLAY, LAYERN, IERR)
		DLL_EXPORT READHEAD
		
		CHARACTER*180 	NAME
		INTEGER			PER
		INTEGER			STP
		REAL 			HEAD(0:NX*NY-1)
		INTEGER			NX
		INTEGER			NY
		INTEGER			NLAY
		INTEGER			LAYERN
		INTEGER 		IERR
		
		INTEGER			KSTP
		INTEGER			KPER
		REAL			PERTIM
		REAL  			TOTIM
		CHARACTER*16 	TEXT
		INTEGER			NC
		INTEGER			NR
		INTEGER			K
        
		IERR = 0
		
     	OPEN(1, FILE = TRIM(NAME), FORM = 'UNFORMATTED', ERR = 50)
        
30		DO NL = 1, NLAY
			READ(1, END = 50) KSTP, KPER, PERTIM, TOTIM, TEXT, NC, NR, K
			READ(1, END = 50) HEAD
			        
			IF (PER.EQ.KPER.AND.STP.EQ.KSTP.AND.LAYERN.EQ.K) THEN
				GOTO 999
			END IF			
		END DO
		
		GOTO 30
		
50		IERR = 1

999		CLOSE(1)
		END
	  
!///////////////////////////////////////////////////////////////////////
!
!	CONTIME 															
!																		
!	Read times for at which concentrations are output.
!																		
!	NAME	: path and filename to read from	
!	NOTIMES : number of times
!	TIMES   : array to store the times
!	NX		: number of columns
!	NY		: number of rows
!	NLAY	: number of layers
!	LAYERN	: layer to get heads from 
!	IERR	: error if eqaul to 1
!
!	KSTP	: time step read from file
!	KPER	: stress period read from file
!	PERTIM	: elapsed time within stress period
!	TOTIM	: total elapsed time since the beginning of simulation
!	TEXT	: drawdown or head
!	NC		: number of columns
!	NR		: number of rows
!	K		: layer number
!
!///////////////////////////////////////////////////////////////////////

		SUBROUTINE CONTIME(NAME, NOTIMES, TIMES, NX, NY, NLAY, IERR)
		DLL_EXPORT CONTIME
	
		CHARACTER*180 	NAME
		INTEGER 		NOTIMES
		REAL   			TIMES(0:NOTIMES-1)
		INTEGER			NX
		INTEGER			NY
		INTEGER			NLAY
		INTEGER			IERR

		INTEGER			KSTP
		INTEGER			KPER
		REAL			PERTIM
		REAL  			TOTIM
		CHARACTER*16 	TEXT
		INTEGER			NC
		INTEGER			NR
		INTEGER			K
		INTEGER 		INDEX
		INTEGER			EXIST
	
		REAL 			CON(0:NX*NY-1)
		
		INTEGER			I

		IERR = 0
		EXIST = 0

		OPEN(1, FILE = TRIM(NAME), FORM = 'UNFORMATTED', ERR = 50)

		I = 0

30		DO NL = 1, NLAY
			EXIST = 0

			READ(1, END = 999) KSTP, KPER, PERTIM, TOTIM, TEXT, NC, NR, K
			READ(1, END = 999) CON
			
			DO NI = 0, I-1
				IF (TOTIM.EQ.TIMES(NI)) THEN
					EXIST = 1
				END IF
			END DO

			IF (EXIST.EQ.0) THEN
				TIMES(I) = TOTIM
				I = I + 1
			END IF
		END DO

		GOTO 30       

50		IERR = 1

999		NOTIMES	= I
		CLOSE(1)
		END

!///////////////////////////////////////////////////////////////////////
!																		
!	READCON 															
!																		
!	Read concentration.                           					
!																		
!	NAME	: path and filename to read from	
!	TIME	: 
!	NPRS	: 
!	CON		:
!	NX		: number of columns
!	NY		: number of rows
!	NLAY	: number of layers
!	LAYERN	: layer to get heads from 
!	IERR	: error if eqaul to 1
!
!	KSTP	: time step read from file
!	KPER	: stress period read from file
!	PERTIM	: elapsed time within stress period
!	TOTIM	: total elapsed time since the beginning of simulation
!	TEXT	: drawdown or head
!	NC		: number of columns
!	NR		: number of rows
!	K		: layer number
!
!///////////////////////////////////////////////////////////////////////

		SUBROUTINE READCON(NAME, TIME, CON, NX, NY, NLAY, LAYERN, IERR)
		DLL_EXPORT READCON

		CHARACTER*180 	NAME
		REAL			TIME
		INTEGER			NPRS
		REAL  			CON(0:NX*NY-1)
		INTEGER			NX
		INTEGER			NY
		INTEGER			NLAY
		INTEGER			LAYERN
		INTEGER 		IERR

		INTEGER			KSTP
		INTEGER			KPER
		REAL			PERTIM
		REAL  			TOTIM
		CHARACTER*16 	TEXT
		INTEGER			NC
		INTEGER			NR
		INTEGER			K

		IERR = 0

		OPEN(1, FILE = TRIM(NAME), FORM = 'UNFORMATTED', ERR = 50)
	
30		DO NL = 1, NLAY
			READ(1, END = 50) KSTP, KPER, PERTIM, TOTIM, TEXT, NC, NR, K
			READ(1, END = 50) CON

			IF (K.EQ.LAYERN.AND.ABS(TIME - TOTIM).LE.1.0E-6) THEN
				GOTO 999
			END IF
		END DO
		
		GOTO 30

50		IERR = 1

999		CLOSE(1)
   		END