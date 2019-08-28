// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"

SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	ObjectAttrFileName = FString("ObjectAttribute.json");
	ResourceAttrFileName = FString("ResourceAttribute.json");
	CompoundTableFileName = FString("CompoundTable.json");

	RelativePath = FString("Res/ConfigData/");


}

void SlAiJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		//��ȡ����
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));
		//��ȡ�浵����
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));
		for (int i = 0; i < RecordDataArray.Num(); ++i)
		{
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			RecordDataList.Add(RecordDataName);
		}
	}
	else {
		SlAiHelper::Debug(FString("Deserialize Failed"));
	}
}

void SlAiJsonHandle::UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> BaseDataArray;

	TSharedPtr<FJsonObject> CultureObject = MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture", Culture);
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObject));

	TSharedPtr<FJsonObject> MusicVolumeObject = MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume", MusicVolume);
	TSharedPtr<FJsonValueObject> MusicVolumeValue = MakeShareable(new FJsonValueObject(MusicVolumeObject));

	TSharedPtr<FJsonObject> SoundVolumeObject = MakeShareable(new FJsonObject);
	SoundVolumeObject->SetNumberField("SoundVolume", SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue = MakeShareable(new FJsonValueObject(SoundVolumeObject));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;

	for (int i = 0; i < RecordDataList->Num(); ++i) {
		TSharedPtr<FJsonObject> RecordItem = MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i), (*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordItem));
		RecordDataArray.Add(RecordDataValue);
	}

	TSharedPtr<FJsonObject> RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData", RecordDataArray);
	TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordDataObject));

	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);

	JsonObject->SetArrayField("T", BaseDataArray);

	FString JsonStr;
	GetFStringInJsonData(JsonObject, JsonStr);

	//SlAiHelper::Debug(FString("Origin Str : " + JsonStr), 60.f);

	//ȥ�������ַ�
	JsonStr.RemoveAt(0, 8);
	JsonStr.RemoveFromEnd(FString("}"));

	//SlAiHelper::Debug(FString("Final Str : " + JsonStr), 60.f);

	//д���ļ�
	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);

}

void SlAiJsonHandle::ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap)
{
	FString JsonValue;
	//���ļ���JSONת����FString
	LoadStringFromFile(ObjectAttrFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader,JsonParsed))
	{
		for (int i = 0; i < JsonParsed.Num(); ++i)
		{
			TArray<TSharedPtr<FJsonValue>> ObjectAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i));
			FText EN = FText::FromString(ObjectAttr[0]->AsObject()->GetStringField("EN"));
			FText ZH = FText::FromString(ObjectAttr[1]->AsObject()->GetStringField("ZH"));
			FString ObjectTypeStr = ObjectAttr[2]->AsObject()->GetStringField("ObjectType");
			int PlantAttack = ObjectAttr[3]->AsObject()->GetIntegerField("PlantAttack");
			int MetalAttcck = ObjectAttr[4]->AsObject()->GetIntegerField("MetalAttcck");
			int AnimalAttack = ObjectAttr[5]->AsObject()->GetIntegerField("AnimalAttack");
			int AffectRange = ObjectAttr[6]->AsObject()->GetIntegerField("AffectRange");
			FString TexPath = ObjectAttr[7]->AsObject()->GetStringField("TexPath");

			//�ַ���ת��ΪEObjectType::Type
			EObjectType::Type ObjectType = StringToObjectType(ObjectTypeStr);
			TSharedPtr<ObjectAttribute> ObjectAttrPtr = MakeShareable(new ObjectAttribute(EN, ZH, ObjectType, PlantAttack, MetalAttcck, AnimalAttack, AffectRange, TexPath));

			ObjectAttrMap.Add(i, ObjectAttrPtr);
		}
	}
	else {
		SlAiHelper::Debug(FString("Deserialize Failed"));
	}
}

bool SlAiJsonHandle::LoadStringFromFile(const FString & FileName, const FString & RelaPath, FString & ResultString)
{
	if (!FileName.IsEmpty()) {
		//��ȡ����·��
		FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsoPath)) {
			if (FFileHelper::LoadFileToString(ResultString, *AbsoPath))
			{
				return true;
			}
			else {
				//���ز��ɹ�
				SlAiHelper::Debug(FString("Load Error") + AbsoPath);
			}
		}
		else {
			//����ļ�������
			SlAiHelper::Debug(FString("File Not Exist") + AbsoPath);
		}
	}
	return false;
}

bool SlAiJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid() && JsonObj->Values.Num() > 0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), JsonWriter);
		return true;
	}
	return false;
}

bool SlAiJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (!JsonStr.IsEmpty()) {
		if (!FileName.IsEmpty()) {
			FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
			//����
			if (FFileHelper::SaveStringToFile(JsonStr, *AbsoPath)) {
				return true;
			}
			else {
				SlAiHelper::Debug(FString("Save") + AbsoPath + FString("-->Failed"), 10.f);
			}
		}
	}
	return false;
}

EObjectType::Type SlAiJsonHandle::StringToObjectType(const FString ArgStr)
{
	if (ArgStr.Equals(FString("Normal"))) return EObjectType::Normal;
	if (ArgStr.Equals(FString("Food"))) return EObjectType::Food;
	if (ArgStr.Equals(FString("Tool"))) return EObjectType::Tool;
	if (ArgStr.Equals(FString("Weapon"))) return EObjectType::Weapon;
	return EObjectType::Normal;
}
