#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Robot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Robot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c ../UART.X/uart1.c ../interrupts.c robot.c ../DRV8833.X/DRV8833.c ../ADC.X/adc.c ../ADC.X/timer3.c ../PWM.X/pwm1.c ../PWM.X/pwm2.c ../PWM.X/pwm3.c ../PWM.X/pwm4.c ../PWM.X/timer2.c communication_protocol.c ../Encoder.X/encoder.c timer4.c ../PWM.X/pwm5.c ../I2C.X/i2c2.c ../VLX.X/tof.c IO.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/1714598041/uart1.o ${OBJECTDIR}/_ext/1472/interrupts.o ${OBJECTDIR}/robot.o ${OBJECTDIR}/_ext/857614013/DRV8833.o ${OBJECTDIR}/_ext/2143051099/adc.o ${OBJECTDIR}/_ext/2143051099/timer3.o ${OBJECTDIR}/_ext/2137487743/pwm1.o ${OBJECTDIR}/_ext/2137487743/pwm2.o ${OBJECTDIR}/_ext/2137487743/pwm3.o ${OBJECTDIR}/_ext/2137487743/pwm4.o ${OBJECTDIR}/_ext/2137487743/timer2.o ${OBJECTDIR}/communication_protocol.o ${OBJECTDIR}/_ext/841585065/encoder.o ${OBJECTDIR}/timer4.o ${OBJECTDIR}/_ext/2137487743/pwm5.o ${OBJECTDIR}/_ext/2145064267/i2c2.o ${OBJECTDIR}/_ext/2132263747/tof.o ${OBJECTDIR}/IO.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/_ext/1714598041/uart1.o.d ${OBJECTDIR}/_ext/1472/interrupts.o.d ${OBJECTDIR}/robot.o.d ${OBJECTDIR}/_ext/857614013/DRV8833.o.d ${OBJECTDIR}/_ext/2143051099/adc.o.d ${OBJECTDIR}/_ext/2143051099/timer3.o.d ${OBJECTDIR}/_ext/2137487743/pwm1.o.d ${OBJECTDIR}/_ext/2137487743/pwm2.o.d ${OBJECTDIR}/_ext/2137487743/pwm3.o.d ${OBJECTDIR}/_ext/2137487743/pwm4.o.d ${OBJECTDIR}/_ext/2137487743/timer2.o.d ${OBJECTDIR}/communication_protocol.o.d ${OBJECTDIR}/_ext/841585065/encoder.o.d ${OBJECTDIR}/timer4.o.d ${OBJECTDIR}/_ext/2137487743/pwm5.o.d ${OBJECTDIR}/_ext/2145064267/i2c2.o.d ${OBJECTDIR}/_ext/2132263747/tof.o.d ${OBJECTDIR}/IO.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/1714598041/uart1.o ${OBJECTDIR}/_ext/1472/interrupts.o ${OBJECTDIR}/robot.o ${OBJECTDIR}/_ext/857614013/DRV8833.o ${OBJECTDIR}/_ext/2143051099/adc.o ${OBJECTDIR}/_ext/2143051099/timer3.o ${OBJECTDIR}/_ext/2137487743/pwm1.o ${OBJECTDIR}/_ext/2137487743/pwm2.o ${OBJECTDIR}/_ext/2137487743/pwm3.o ${OBJECTDIR}/_ext/2137487743/pwm4.o ${OBJECTDIR}/_ext/2137487743/timer2.o ${OBJECTDIR}/communication_protocol.o ${OBJECTDIR}/_ext/841585065/encoder.o ${OBJECTDIR}/timer4.o ${OBJECTDIR}/_ext/2137487743/pwm5.o ${OBJECTDIR}/_ext/2145064267/i2c2.o ${OBJECTDIR}/_ext/2132263747/tof.o ${OBJECTDIR}/IO.o

# Source Files
SOURCEFILES=main.c ../UART.X/uart1.c ../interrupts.c robot.c ../DRV8833.X/DRV8833.c ../ADC.X/adc.c ../ADC.X/timer3.c ../PWM.X/pwm1.c ../PWM.X/pwm2.c ../PWM.X/pwm3.c ../PWM.X/pwm4.c ../PWM.X/timer2.c communication_protocol.c ../Encoder.X/encoder.c timer4.c ../PWM.X/pwm5.c ../I2C.X/i2c2.c ../VLX.X/tof.c IO.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Robot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1714598041/uart1.o: ../UART.X/uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1714598041" 
	@${RM} ${OBJECTDIR}/_ext/1714598041/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714598041/uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1714598041/uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1714598041/uart1.o.d" -o ${OBJECTDIR}/_ext/1714598041/uart1.o ../UART.X/uart1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/interrupts.o: ../interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/interrupts.o.d" -o ${OBJECTDIR}/_ext/1472/interrupts.o ../interrupts.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/robot.o: robot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/robot.o.d 
	@${RM} ${OBJECTDIR}/robot.o 
	@${FIXDEPS} "${OBJECTDIR}/robot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/robot.o.d" -o ${OBJECTDIR}/robot.o robot.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/857614013/DRV8833.o: ../DRV8833.X/DRV8833.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/857614013" 
	@${RM} ${OBJECTDIR}/_ext/857614013/DRV8833.o.d 
	@${RM} ${OBJECTDIR}/_ext/857614013/DRV8833.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/857614013/DRV8833.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/857614013/DRV8833.o.d" -o ${OBJECTDIR}/_ext/857614013/DRV8833.o ../DRV8833.X/DRV8833.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2143051099/adc.o: ../ADC.X/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2143051099" 
	@${RM} ${OBJECTDIR}/_ext/2143051099/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2143051099/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2143051099/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2143051099/adc.o.d" -o ${OBJECTDIR}/_ext/2143051099/adc.o ../ADC.X/adc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2143051099/timer3.o: ../ADC.X/timer3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2143051099" 
	@${RM} ${OBJECTDIR}/_ext/2143051099/timer3.o.d 
	@${RM} ${OBJECTDIR}/_ext/2143051099/timer3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2143051099/timer3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2143051099/timer3.o.d" -o ${OBJECTDIR}/_ext/2143051099/timer3.o ../ADC.X/timer3.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm1.o: ../PWM.X/pwm1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm1.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm1.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm1.o ../PWM.X/pwm1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm2.o: ../PWM.X/pwm2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm2.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm2.o ../PWM.X/pwm2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm3.o: ../PWM.X/pwm3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm3.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm3.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm3.o ../PWM.X/pwm3.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm4.o: ../PWM.X/pwm4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm4.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm4.o ../PWM.X/pwm4.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/timer2.o: ../PWM.X/timer2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/timer2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/timer2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/timer2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/timer2.o.d" -o ${OBJECTDIR}/_ext/2137487743/timer2.o ../PWM.X/timer2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/communication_protocol.o: communication_protocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/communication_protocol.o.d 
	@${RM} ${OBJECTDIR}/communication_protocol.o 
	@${FIXDEPS} "${OBJECTDIR}/communication_protocol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/communication_protocol.o.d" -o ${OBJECTDIR}/communication_protocol.o communication_protocol.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/841585065/encoder.o: ../Encoder.X/encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/841585065" 
	@${RM} ${OBJECTDIR}/_ext/841585065/encoder.o.d 
	@${RM} ${OBJECTDIR}/_ext/841585065/encoder.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/841585065/encoder.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/841585065/encoder.o.d" -o ${OBJECTDIR}/_ext/841585065/encoder.o ../Encoder.X/encoder.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/timer4.o: timer4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer4.o.d 
	@${RM} ${OBJECTDIR}/timer4.o 
	@${FIXDEPS} "${OBJECTDIR}/timer4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer4.o.d" -o ${OBJECTDIR}/timer4.o timer4.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm5.o: ../PWM.X/pwm5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm5.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm5.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm5.o ../PWM.X/pwm5.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2145064267/i2c2.o: ../I2C.X/i2c2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2145064267" 
	@${RM} ${OBJECTDIR}/_ext/2145064267/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2145064267/i2c2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2145064267/i2c2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2145064267/i2c2.o.d" -o ${OBJECTDIR}/_ext/2145064267/i2c2.o ../I2C.X/i2c2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2132263747/tof.o: ../VLX.X/tof.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2132263747" 
	@${RM} ${OBJECTDIR}/_ext/2132263747/tof.o.d 
	@${RM} ${OBJECTDIR}/_ext/2132263747/tof.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2132263747/tof.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2132263747/tof.o.d" -o ${OBJECTDIR}/_ext/2132263747/tof.o ../VLX.X/tof.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/IO.o: IO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IO.o.d 
	@${RM} ${OBJECTDIR}/IO.o 
	@${FIXDEPS} "${OBJECTDIR}/IO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/IO.o.d" -o ${OBJECTDIR}/IO.o IO.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1714598041/uart1.o: ../UART.X/uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1714598041" 
	@${RM} ${OBJECTDIR}/_ext/1714598041/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714598041/uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1714598041/uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1714598041/uart1.o.d" -o ${OBJECTDIR}/_ext/1714598041/uart1.o ../UART.X/uart1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/interrupts.o: ../interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/interrupts.o.d" -o ${OBJECTDIR}/_ext/1472/interrupts.o ../interrupts.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/robot.o: robot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/robot.o.d 
	@${RM} ${OBJECTDIR}/robot.o 
	@${FIXDEPS} "${OBJECTDIR}/robot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/robot.o.d" -o ${OBJECTDIR}/robot.o robot.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/857614013/DRV8833.o: ../DRV8833.X/DRV8833.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/857614013" 
	@${RM} ${OBJECTDIR}/_ext/857614013/DRV8833.o.d 
	@${RM} ${OBJECTDIR}/_ext/857614013/DRV8833.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/857614013/DRV8833.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/857614013/DRV8833.o.d" -o ${OBJECTDIR}/_ext/857614013/DRV8833.o ../DRV8833.X/DRV8833.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2143051099/adc.o: ../ADC.X/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2143051099" 
	@${RM} ${OBJECTDIR}/_ext/2143051099/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2143051099/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2143051099/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2143051099/adc.o.d" -o ${OBJECTDIR}/_ext/2143051099/adc.o ../ADC.X/adc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2143051099/timer3.o: ../ADC.X/timer3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2143051099" 
	@${RM} ${OBJECTDIR}/_ext/2143051099/timer3.o.d 
	@${RM} ${OBJECTDIR}/_ext/2143051099/timer3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2143051099/timer3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2143051099/timer3.o.d" -o ${OBJECTDIR}/_ext/2143051099/timer3.o ../ADC.X/timer3.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm1.o: ../PWM.X/pwm1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm1.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm1.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm1.o ../PWM.X/pwm1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm2.o: ../PWM.X/pwm2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm2.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm2.o ../PWM.X/pwm2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm3.o: ../PWM.X/pwm3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm3.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm3.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm3.o ../PWM.X/pwm3.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm4.o: ../PWM.X/pwm4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm4.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm4.o ../PWM.X/pwm4.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/timer2.o: ../PWM.X/timer2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/timer2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/timer2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/timer2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/timer2.o.d" -o ${OBJECTDIR}/_ext/2137487743/timer2.o ../PWM.X/timer2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/communication_protocol.o: communication_protocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/communication_protocol.o.d 
	@${RM} ${OBJECTDIR}/communication_protocol.o 
	@${FIXDEPS} "${OBJECTDIR}/communication_protocol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/communication_protocol.o.d" -o ${OBJECTDIR}/communication_protocol.o communication_protocol.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/841585065/encoder.o: ../Encoder.X/encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/841585065" 
	@${RM} ${OBJECTDIR}/_ext/841585065/encoder.o.d 
	@${RM} ${OBJECTDIR}/_ext/841585065/encoder.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/841585065/encoder.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/841585065/encoder.o.d" -o ${OBJECTDIR}/_ext/841585065/encoder.o ../Encoder.X/encoder.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/timer4.o: timer4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer4.o.d 
	@${RM} ${OBJECTDIR}/timer4.o 
	@${FIXDEPS} "${OBJECTDIR}/timer4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer4.o.d" -o ${OBJECTDIR}/timer4.o timer4.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm5.o: ../PWM.X/pwm5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm5.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm5.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm5.o ../PWM.X/pwm5.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2145064267/i2c2.o: ../I2C.X/i2c2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2145064267" 
	@${RM} ${OBJECTDIR}/_ext/2145064267/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2145064267/i2c2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2145064267/i2c2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2145064267/i2c2.o.d" -o ${OBJECTDIR}/_ext/2145064267/i2c2.o ../I2C.X/i2c2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2132263747/tof.o: ../VLX.X/tof.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2132263747" 
	@${RM} ${OBJECTDIR}/_ext/2132263747/tof.o.d 
	@${RM} ${OBJECTDIR}/_ext/2132263747/tof.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2132263747/tof.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2132263747/tof.o.d" -o ${OBJECTDIR}/_ext/2132263747/tof.o ../VLX.X/tof.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/IO.o: IO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IO.o.d 
	@${RM} ${OBJECTDIR}/IO.o 
	@${FIXDEPS} "${OBJECTDIR}/IO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/IO.o.d" -o ${OBJECTDIR}/IO.o IO.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Robot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DPK3OBPlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Robot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=PK3OBPlatformTool=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Robot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Robot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Robot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
