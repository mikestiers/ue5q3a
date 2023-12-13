// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsMenuWidget.h"
#include "Components/Slider.h"
#include "AudioDevice.h"
#include "Sound/SoundMix.h"
#include "GameFramework/GameUserSettings.h"

void USettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind delegates here
	if (VolumeSlider)
	{
		VolumeSlider->Value = 1.0f;
		VolumeSlider->OnValueChanged.AddDynamic(this, &USettingsMenuWidget::OnVolumeSliderValueChanged);
	}
}

void USettingsMenuWidget::OnVolumeSliderValueChanged(float Value)
{
	//GetWorld()->GetAudioDevice()->GetSoundMixClass()->SetSoundMixClassOverride(USoundMix::DefaultSoundMix, Value, 1.0f, 0.0f, 0.0f);
	//UGameUserSettings::GetGameUserSettings()->SetMasterSoundVolume(Value);
}
