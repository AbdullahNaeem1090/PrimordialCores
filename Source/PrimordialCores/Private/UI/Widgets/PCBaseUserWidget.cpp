// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PCBaseUserWidget.h"

void UPCBaseUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
