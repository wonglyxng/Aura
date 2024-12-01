// @wanglixiang

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 可以通过蓝图调用
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	// UAuraUserWidget类需要包含一个AuraWidgetController对象用来处理各种操作，View-Controller-Model(MVC)模型
	// 每个AuraUserWidget都包含控制器
	// 控制器不知道哪些widgets与之相关联，但是widgets知道关联的控制器是谁
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	// BlueprintImplementableEvent: 在C++可以声明函数(但不能定义, 由蓝图重写), 在C++里调用该函数, 蓝图重写实现该函数 [没有自由]
	// 每当我们初始化 WidgetController 的时候同时也调用此函数, 这样我们可以实现在蓝图中做我们想做的事情
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
