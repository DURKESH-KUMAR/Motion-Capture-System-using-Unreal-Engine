// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControlRig.h"
#include "ControlRigDisplaySettings.h"
#include "ControlRigGizmoActor.h"

#include "ControlRigDrawer.generated.h"



UCLASS(Blueprintable, BlueprintType)
class MEDIAPIPEMOTION_API AControlRigDrawer : public AActor
{
	GENERATED_BODY()

	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Draw")
	FControlRigDisplaySettings DisplaySettings;
	
	inline static TWeakObjectPtr<AControlRigDrawer> Default;
	// Sets default values for this actor's properties
	AControlRigDrawer();

	FGuid CreateShapeActors(USkeletalMeshComponent* Component, UControlRig* ControlRig, TArray<FName>* DisplayControls = nullptr);

	void TickControlShape(FGuid ControlRigID, const FTransform& ComponentTransform);
	bool ContainsControlRig(UControlRig* ControlRig) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	struct FControlRigRenderingTask
	{
		FGuid ControlRigID;
		FTransform ComponentTransform;
	};
	void Refresh(const FControlRigRenderingTask& Task);
	void HandleObjectsReinstanced(const TMap<UObject*, UObject*>&  OldToNewInstanceMap);
	TArray<FGuid> TempIDs;
	bool DestroyShapesActors(FGuid ControlRigID, bool bRemoveID);
	bool ShapeSelectionOverride(const UPrimitiveComponent* PrimitiveComponent);
	inline static FCriticalSection InstanceMutex{};
	bool bEnd = false;
	inline static FRWLock ListLock{};
	TArray<TWeakObjectPtr<UControlRig>> RuntimeControlRigs;
	TArray<FGuid> ControlRigIDs;

	TMap<FGuid, TArray<AControlRigShapeActor*>> ControlRigShapeActors;
	TMap<FGuid, TWeakObjectPtr<USkeletalMeshComponent>> ControlRigComponents;
	TQueue<FControlRigRenderingTask> RenderingTask;
};
