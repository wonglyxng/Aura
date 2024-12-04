// @wanglixiang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Cobmat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	UPROPERTY()
	UAttributeSet* AttributeSet = nullptr;


};
