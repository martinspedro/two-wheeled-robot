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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DRV8833.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DRV8833.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=DRV8833.c main.c ../ADC.X/adc.c ../PWM.X/pwm1.c ../PWM.X/pwm2.c ../PWM.X/pwm3.c ../PWM.X/pwm4.c ../PWM.X/timer2.c ../PWM.X/pwm5.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/DRV8833.o ${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/2143051099/adc.o ${OBJECTDIR}/_ext/2137487743/pwm1.o ${OBJECTDIR}/_ext/2137487743/pwm2.o ${OBJECTDIR}/_ext/2137487743/pwm3.o ${OBJECTDIR}/_ext/2137487743/pwm4.o ${OBJECTDIR}/_ext/2137487743/timer2.o ${OBJECTDIR}/_ext/2137487743/pwm5.o
POSSIBLE_DEPFILES=${OBJECTDIR}/DRV8833.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/_ext/2143051099/adc.o.d ${OBJECTDIR}/_ext/2137487743/pwm1.o.d ${OBJECTDIR}/_ext/2137487743/pwm2.o.d ${OBJECTDIR}/_ext/2137487743/pwm3.o.d ${OBJECTDIR}/_ext/2137487743/pwm4.o.d ${OBJECTDIR}/_ext/2137487743/timer2.o.d ${OBJECTDIR}/_ext/2137487743/pwm5.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/DRV8833.o ${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/2143051099/adc.o ${OBJECTDIR}/_ext/2137487743/pwm1.o ${OBJECTDIR}/_ext/2137487743/pwm2.o ${OBJECTDIR}/_ext/2137487743/pwm3.o ${OBJECTDIR}/_ext/2137487743/pwm4.o ${OBJECTDIR}/_ext/2137487743/timer2.o ${OBJECTDIR}/_ext/2137487743/pwm5.o

# Source Files
SOURCEFILES=DRV8833.c main.c ../ADC.X/adc.c ../PWM.X/pwm1.c ../PWM.X/pwm2.c ../PWM.X/pwm3.c ../PWM.X/pwm4.c ../PWM.X/timer2.c ../PWM.X/pwm5.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/DRV8833.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/DRV8833.o: DRV8833.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DRV8833.o.d 
	@${RM} ${OBJECTDIR}/DRV8833.o 
	@${FIXDEPS} "${OBJECTDIR}/DRV8833.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DRV8833.o.d" -o ${OBJECTDIR}/DRV8833.o DRV8833.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2143051099/adc.o: ../ADC.X/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2143051099" 
	@${RM} ${OBJECTDIR}/_ext/2143051099/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2143051099/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2143051099/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2143051099/adc.o.d" -o ${OBJECTDIR}/_ext/2143051099/adc.o ../ADC.X/adc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm1.o: ../PWM.X/pwm1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm1.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm1.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm1.o ../PWM.X/pwm1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm2.o: ../PWM.X/pwm2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm2.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm2.o ../PWM.X/pwm2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm3.o: ../PWM.X/pwm3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm3.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm3.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm3.o ../PWM.X/pwm3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm4.o: ../PWM.X/pwm4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm4.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm4.o ../PWM.X/pwm4.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/timer2.o: ../PWM.X/timer2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/timer2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/timer2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/timer2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/timer2.o.d" -o ${OBJECTDIR}/_ext/2137487743/timer2.o ../PWM.X/timer2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm5.o: ../PWM.X/pwm5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm5.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPK3OBPlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm5.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm5.o ../PWM.X/pwm5.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/DRV8833.o: DRV8833.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DRV8833.o.d 
	@${RM} ${OBJECTDIR}/DRV8833.o 
	@${FIXDEPS} "${OBJECTDIR}/DRV8833.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DRV8833.o.d" -o ${OBJECTDIR}/DRV8833.o DRV8833.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2143051099/adc.o: ../ADC.X/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2143051099" 
	@${RM} ${OBJECTDIR}/_ext/2143051099/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2143051099/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2143051099/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2143051099/adc.o.d" -o ${OBJECTDIR}/_ext/2143051099/adc.o ../ADC.X/adc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm1.o: ../PWM.X/pwm1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm1.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm1.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm1.o ../PWM.X/pwm1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm2.o: ../PWM.X/pwm2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm2.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm2.o ../PWM.X/pwm2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm3.o: ../PWM.X/pwm3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm3.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm3.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm3.o ../PWM.X/pwm3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm4.o: ../PWM.X/pwm4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm4.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm4.o ../PWM.X/pwm4.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/timer2.o: ../PWM.X/timer2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/timer2.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/timer2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/timer2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/timer2.o.d" -o ${OBJECTDIR}/_ext/2137487743/timer2.o ../PWM.X/timer2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2137487743/pwm5.o: ../PWM.X/pwm5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137487743" 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm5.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137487743/pwm5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137487743/pwm5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2137487743/pwm5.o.d" -o ${OBJECTDIR}/_ext/2137487743/pwm5.o ../PWM.X/pwm5.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DRV8833.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DPK3OBPlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DRV8833.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=PK3OBPlatformTool=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DRV8833.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DRV8833.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DRV8833.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
