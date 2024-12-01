// @wanglixiang


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter()
{
	// 配置角色移动
	GetCharacterMovement()->bOrientRotationToMovement = true; // 角色朝输入的方向移动   
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 840.0f, 0.0f); // 以此旋转速度
	GetCharacterMovement()->bConstrainToPlane = true; // 因为我们是俯视角游戏，所以需要强制角色运动限制在平面上
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 开始时对齐角色和平面，保证具有正确的位置和方向


	// Don't rotate when the controller rotates. Let that just affect the camera
	// 角色不应该使用控制器的旋转，所以不要在控制器旋转时旋转。让这仅仅影响摄像机，也就是说摄像机随控制器旋转时旋转，
	// 其实相机的旋转也不是我们想要的，我们希望俯视角游戏是固定相机，那么这个需要将摄像机的这三个参数也设置为false，由于我们是通过蓝图创建相机的，
	// 所以相机的控制需要在蓝图中去设置
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// init ability actor for server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// init ability actor for client
	InitAbilityActorInfo();

}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController())) {
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD())) {
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
