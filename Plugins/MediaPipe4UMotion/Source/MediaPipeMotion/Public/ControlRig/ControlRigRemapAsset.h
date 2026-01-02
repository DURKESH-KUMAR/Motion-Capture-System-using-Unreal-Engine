// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "ControlRig.h"
#include "ControlRigMapping.h"
#include "MediaPipeControlRigElement.h"
#include "RigControls.h"
#if WITH_EDITOR
#include "ControlRigBlueprint.h"
#endif
#include "ControlRigRemapAsset.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, NotBlueprintable, hideCategories=Object)
class MEDIAPIPEMOTION_API UControlRigRemapAsset : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category="ControlRig")
	TSubclassOf<UControlRig> ControlRigClass;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement RootIKCtrl  = FMediaPipeControlRigElement::None;
	
	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement BodyIKCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement SpineIKCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement ChestIKCtrl  = FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement HeadIKCtrl  =  FMediaPipeControlRigElement::None;
	
	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement LeftHandIKCtrl =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement RightHandIKCtrl  = FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
    FMediaPipeControlRigElement LeftArmPoleIKCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement RightArmPoleIKCtrl  = FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement LeftFootIKCtrl =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement RightFootIKCtrl  =  FMediaPipeControlRigElement::None;
	
	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement LeftLegPoleIKCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Body Controls")
	FMediaPipeControlRigElement RightLegPoleIKCtrl  =  FMediaPipeControlRigElement::None;


	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftThumbProximalCtrl =  FMediaPipeControlRigElement::None;
	
	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftThumbIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftThumbDistalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftIndexProximalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftIndexIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftIndexDistalCtrl   =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftMiddleProximalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftMiddleIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftMiddleDistalCtrl   =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftRingProximalCtrl   =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftRingIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftRingDistalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftLittleProximalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftLittleIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Left")
	FMediaPipeControlRigElement LeftLittleDistalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightThumbProximalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightThumbIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightThumbDistalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightIndexProximalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightIndexIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightIndexDistalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightMiddleProximalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightMiddleIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightMiddleDistalCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightRingProximalCtrl   =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightRingIntermediateCtrl   =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightRingDistalCtrl   =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightLittleProximalCtrl  =  FMediaPipeControlRigElement::None;
	
	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightLittleIntermediateCtrl  =  FMediaPipeControlRigElement::None;

	UPROPERTY(EditAnywhere, Category="Fingers Controls | Right")
	FMediaPipeControlRigElement RightLittleDistalCtrl  =  FMediaPipeControlRigElement::None;
	
	void SetControlRig(UControlRig* InControlRig, const FSoftObjectPath& BlueprintPath = FSoftObjectPath{});

	UControlRig* GetControlRig() const;

	void GetMapping(FControlRigMapping& OutMapping) const;

	void SetMapping(const FControlRigMapping& InMapping);

#if WITH_EDITOR
	UControlRigBlueprint* GetControlRigBluePrint() const;
#endif
	
protected:
	UPROPERTY()
	FSoftObjectPath ControlRigBlueprintAssetPath;
private:
	UPROPERTY(Transient)
	mutable  TWeakObjectPtr<UControlRig> ControlRig;

};