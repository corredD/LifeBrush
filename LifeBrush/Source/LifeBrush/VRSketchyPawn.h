// Copyright 2016, Timothy Davison. All rights reserved.

#pragma once

#include "GameFramework/Pawn.h"

#include "VRTool.h"
#include "ShipEditorSimulation/GraphSnapshot.h"

#include "VRSketchyPawn.generated.h"


class UMotionControllerComponent;
class URegionGrowingComponent;
class UFlexSimulationComponent;
class USelectionTool;
class UGenerativeBrushTool;
class UDigTool;
class UMeshCollectionTool;
class UEventVisualizationTool;
class UAgentPathlineTool;
class UPhysicalInteractionTool;
class UDiscreteElementEditorComponent;
class URegionGrowingGeneratorTool;
class UStringGeneratorTool;
class UCollagenGeneratorTool;
class USwarmGeneratorTool;
class URegionGrowing_GenerativeBrushTool;
struct FFlexSimulation;

UENUM(BlueprintType)
enum class ESketchyInteractionMode : uint8
{
	Painting UMETA(DisplayName = "Painting"),
	Simulating UMETA(DisplayName = "Simulating"),
};

UCLASS( DefaultToInstanced )
class LIFEBRUSH_API AVRSketchyPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ShipEditor")
	bool developerMode = true;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ShipEditor" )
	USceneComponent * vrScene;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ShipEditor" )
	UCameraComponent * camera;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ShipEditor" )
	UMotionControllerComponent * leftController;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ShipEditor" )
	UMotionControllerComponent * rightController;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ShipEditor" )
	UStaticMeshComponent * rightInteractionPoint;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ShipEditor" )
	UStaticMeshComponent * leftInteractionPoint;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ShipEditor" )
	UWidgetComponent * rightPadWidget;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ShipEditor" )
	UWidgetComponent * rightSelectionPointWidget;

	UPROPERTY( EditInstanceOnly, BlueprintReadWrite, Category = "ShipEditor" )
	AActor * regionGrowingActor = nullptr;

	UPROPERTY( EditInstanceOnly, BlueprintReadWrite, Category = "ShipEditor" )
	AActor * flexSimulationActor = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ShipEditor")
	AActor * discreteElementEditorActor = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ShipEditor")
	AActor * exemplarActor = nullptr;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor" )
	URegionGrowing_GenerativeBrushTool * generativeBrushTool;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor" )
	URegionGrowingGeneratorTool * regionGrowingElementGeneratorTool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor")
	UStringGeneratorTool * stringGeneratorTool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor")
	UCollagenGeneratorTool * collagenGeneratorTool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor")
	USwarmGeneratorTool * swarmGeneratorTool;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor" )
	USelectionTool * selectionTool;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor" )
	UDigTool * digTool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor")
	UMeshCollectionTool * meshCollectionTool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor")
	UEventVisualizationTool * eventVisualizationTool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor")
	UAgentPathlineTool * agentPathlineTool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "ShipEditor")
	UPhysicalInteractionTool * physicalInteractionTool;

public:
	UFUNCTION(BlueprintCallable, Category = Generation)
	ESketchyInteractionMode interactionMode() { return _interactionMode; }

	UFUNCTION(BlueprintCallable, Category = Generation)
	void setInteractionMode( ESketchyInteractionMode mode );

	UFUNCTION( BlueprintCallable, Category = Generation )
	bool isSimulating();

	UFUNCTION( BlueprintCallable, Category = Generation )
	void setSimulating( bool simulating );

	UFUNCTION( BlueprintCallable, Category = Generation )
	void leftTrigger( float value );

	UFUNCTION( BlueprintCallable, Category = Generation )
	void rightTrigger( float value );

	UFUNCTION( BlueprintCallable, Category = Generation )
	void setCurrentTool(UTool * newCurrentTool);

	UFUNCTION( BlueprintCallable, Category = Generation )
	UTool * getCurrentTool() { return _currentTool; }

	// --------------------
	// Simulation snapshots
	// --------------------
	UFUNCTION(BlueprintCallable, Category = Generation)
	void snapshotSimulation();

	UFUNCTION(BlueprintCallable, Category = Generation)
	void restoreSimulation();

	UFUNCTION(BlueprintCallable, Category = Generation)
	void snapshotSimulationStateToEditor();

	void snapshotMeshInterfaceRuntimeMeshComponentToActor(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = Generation)
	void snapshotSimulationGraphicsToEditor();

protected:
	FGraphSnapshot _snapshot;

protected:
	URegionGrowingComponent * regionGrowingComponent;
	UFlexSimulationComponent * flexComponent;
	FFlexSimulation * flexSimulation;
	UDiscreteElementEditorComponent * editorComponent;

	bool _didInit = false;
	bool _didInitSimulation = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ShipEditor")
	ESketchyInteractionMode	_interactionMode = ESketchyInteractionMode::Painting;

	UTool * _currentTool;

	bool _leftTriggerDown = false;
	bool _rightTriggerDown = false;

	float _lastLeftTriggerValue = 0.0f;
	float _lastRightTriggerValue = 0.0f;

	bool _wantsLeftSpiderMan = false;
	bool _wantsRightSpiderMan = false;


	FVector _lastLeft;
	FVector _lastRight;


	int _simulationSnapShotCount = 0;

	bool _leftTouchActive = false;
	bool _rightTouchActive = false;

public:
	// Sets default values for this pawn's properties
	AVRSketchyPawn();

	virtual void PreInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void spiderManLeftStart();
	void spiderManLeftEnd();
	void spiderManLeftUpdate();

	void spiderManRightStart();
	void spiderManRightEnd();
	void spiderManRightUpdate();

protected:
	void _initSimulation_oneTime();
	void _initSimulationBounds();
	void _initTools();

	FString _actorLabelByDate(FString baseName);

	void takeGraphicalSnapshotAndHighResShot();
	void takeHighReshShot();
	void snapshotElementDomain();

	void leftController_touchStart();
	void leftController_touchUpdated();
	void leftController_touchEnd();
	FVector2D _getLeftTouchPoint();

	void leftController_upFace();
	void leftController_downFace();
	void leftController_leftFace();
	void leftController_rightFace();

	void rightController_touchStart();
	void rightController_touchUpdated();
	void rightController_touchEnd();
	FVector2D _getRightTouchPoint();

	void rightController_upFace();
	void rightController_downFace();
	void rightController_leftFace();
	void rightController_rightFace();

	void _startSimulation();
	void _endSimulation();

	void _startCurrentToolLeftTrigger();
	void _startCurrentToolRightTrigger();


};