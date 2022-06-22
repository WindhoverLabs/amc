/****************************************************************************
 *
 *   Copyright (c) 2012-2016 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef MULTIROTOR_MIXER_H
#define MULTIROTOR_MIXER_H

#include "cfe.h"
#include "Mixer.h"
#include "MixerTables.h"


/**
 * Supported multirotor geometries.
 *
 * Values are generated by the multi_tables script and placed to mixer_multirotor.generated.h
 */
//typedef uint32 MultirotorGeometryUnderlyingType;
//enum class MultirotorGeometry : MultirotorGeometryUnderlyingType;

/**
 * Multi-rotor mixer for pre-defined vehicle geometries.
 *
 * Collects four inputs (roll, pitch, yaw, thrust) and mixes them to
 * a set of outputs based on the configured geometry.
 */
class MultirotorMixer : public Mixer
{
public:
	/**
	 * Constructor.
	 *
	 * @param control_cb		Callback invoked to read inputs.
	 * @param cb_handle		Passed to control_cb.
	 * @param geometry		The selected geometry.
	 * @param roll_scale		Scaling factor applied to roll inputs
	 *				compared to thrust.
	 * @param pitch_scale		Scaling factor applied to pitch inputs
	 *				compared to thrust.
	 * @param yaw_wcale		Scaling factor applied to yaw inputs compared
	 *				to thrust.
	 * @param idle_speed		Minimum rotor control output value; usually
	 *				tuned to ensure that rotors never stall at the
	 * 				low end of their control range.
	 */
	MultirotorMixer();
	~MultirotorMixer();

    int32 SetConfig(AMC_MultirotorMixer_Config_t *config);

	virtual uint32		mix(float *outputs, uint32 space, uint16 *status_reg);
	virtual uint16		get_saturation_status(void);
	virtual void		groups_required(uint32 &groups);

    float Contrain(float Value, float Minimum, float Maximum);

	uint32 set_trim(float trim);

	/**
	 * @brief      Sets the thrust factor used to calculate mapping from desired thrust to pwm.
	 *
	 * @param[in]  val   The value
	 */
	virtual void			set_thrust_factor(float val);

    static int32 ValidateConfigTable(void* ConfigTblPtr);
    int32 AcquireConfigPointers(void);
    virtual int32 Initialize(void);

private:
	float 			   m_ThrustFactor;

	typedef union {
		struct {
			uint16 motor_pos	: 1; // 0 - true when any motor has saturated in the positive direction
			uint16 motor_neg	: 1; // 1 - true when any motor has saturated in the negative direction
			uint16 roll_pos	    : 1; // 2 - true when a positive roll demand change will increase saturation
			uint16 roll_neg	    : 1; // 3 - true when a negative roll demand change will increase saturation
			uint16 pitch_pos	: 1; // 4 - true when a positive pitch demand change will increase saturation
			uint16 pitch_neg	: 1; // 5 - true when a negative pitch demand change will increase saturation
			uint16 yaw_pos	    : 1; // 6 - true when a positive yaw demand change will increase saturation
			uint16 yaw_neg	    : 1; // 7 - true when a negative yaw demand change will increase saturation
			uint16 thrust_pos	: 1; // 8 - true when a positive thrust demand change will increase saturation
			uint16 thrust_neg	: 1; // 9 - true when a negative thrust demand change will increase saturation
		} flags;
		uint16 value;
	} SaturationStatus_t;

	SaturationStatus_t m_SaturationStatus;

	void update_saturation_status(uint32 index, bool clipping_high, bool clipping_low);

	float 			   m_OutputsPrev[AMC_MULTIROTOR_MIXER_MAX_ROTOR_COUNT];
	AMC_MultirotorMixer_Config_t *m_Config;

	/* do not allow to copy due to ptr data members */
	MultirotorMixer(const MultirotorMixer &);
	MultirotorMixer operator=(const MultirotorMixer &);
};


#endif
