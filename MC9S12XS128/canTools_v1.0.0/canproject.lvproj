<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="16008000">
	<Item Name="我的电脑" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">我的电脑/VI服务器</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">我的电脑/VI服务器</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Confs" Type="Folder" URL="../Confs">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Datas" Type="Folder" URL="../Datas">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Docs" Type="Folder" URL="../Docs">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Drivers" Type="Folder" URL="../Drivers">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="SysInit" Type="Folder" URL="../SysInit">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="main.vi" Type="VI" URL="../main.vi"/>
		<Item Name="menu.rtm" Type="Document" URL="../menu.rtm"/>
		<Item Name="上传数据转换.vi" Type="VI" URL="../上传数据转换.vi"/>
		<Item Name="依赖关系" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="ClearError.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/ClearError.vi"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="LVMajorAndMinorColorsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVMajorAndMinorColorsTypeDef.ctl"/>
				<Item Name="LVRowAndColumnTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRowAndColumnTypeDef.ctl"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
			<Item Name="64bit-num.vi" Type="VI" URL="../64bit-num.vi"/>
			<Item Name="CloseDevice.vi" Type="VI" URL="../CloseDevice.vi"/>
			<Item Name="ECanVci.dll" Type="Document" URL="../ECanVci.dll"/>
			<Item Name="InitCan.vi" Type="VI" URL="../InitCan.vi"/>
			<Item Name="OpenDevice.vi" Type="VI" URL="../OpenDevice.vi"/>
			<Item Name="receive-waveArray.vi" Type="VI" URL="../receive-waveArray.vi"/>
			<Item Name="Receive.vi" Type="VI" URL="../Receive.vi"/>
			<Item Name="StartCAN.vi" Type="VI" URL="../StartCAN.vi"/>
			<Item Name="str-number.vi" Type="VI" URL="../str-number.vi"/>
			<Item Name="TDMS文件解析.vi" Type="VI" URL="../TDMS文件解析.vi"/>
			<Item Name="Transmit.vi" Type="VI" URL="../Transmit.vi"/>
			<Item Name="txt-array.vi" Type="VI" URL="../txt-array.vi"/>
			<Item Name="保存历史波形图.vi" Type="VI" URL="../保存历史波形图.vi"/>
			<Item Name="保存下载配置.vi" Type="VI" URL="../保存下载配置.vi"/>
			<Item Name="读取发送表.vi" Type="VI" URL="../读取发送表.vi"/>
			<Item Name="多列表初始化.vi" Type="VI" URL="../多列表初始化.vi"/>
			<Item Name="多列表转换.vi" Type="VI" URL="../多列表转换.vi"/>
			<Item Name="发送数组-ccp转换序列.vi" Type="VI" URL="../发送数组-ccp转换序列.vi"/>
			<Item Name="上传数据.vi" Type="VI" URL="../上传数据.vi"/>
			<Item Name="下位机buffer.vi" Type="VI" URL="../下位机buffer.vi"/>
		</Item>
		<Item Name="程序生成规范" Type="Build">
			<Item Name="我的应用程序" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{9F1DDB58-4186-4306-9B1C-208950B6F06F}</Property>
				<Property Name="App_INI_GUID" Type="Str">{E0595201-18B1-4BED-A95C-4478E0798950}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{87E0E6B3-136E-4762-ABC3-77FB03A24715}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">我的应用程序</Property>
				<Property Name="Bld_defaultLanguage" Type="Str">ChineseS</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../我的应用程序</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{7344426F-D574-48DB-A285-F20671F08807}</Property>
				<Property Name="Bld_version.build" Type="Int">13</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">应用程序.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../我的应用程序/应用程序.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">支持目录</Property>
				<Property Name="Destination[1].path" Type="Path">../我的应用程序/SysInit</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[2].destName" Type="Str">Confs</Property>
				<Property Name="Destination[2].path" Type="Path">../我的应用程序/Confs</Property>
				<Property Name="Destination[2].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[3].destName" Type="Str">Datas</Property>
				<Property Name="Destination[3].path" Type="Path">../我的应用程序/Datas</Property>
				<Property Name="Destination[3].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[4].destName" Type="Str">Docs</Property>
				<Property Name="Destination[4].path" Type="Path">../我的应用程序/Docs</Property>
				<Property Name="Destination[4].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[5].destName" Type="Str">Drivers</Property>
				<Property Name="Destination[5].path" Type="Path">../我的应用程序/Drivers</Property>
				<Property Name="Destination[5].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">6</Property>
				<Property Name="Source[0].itemID" Type="Str">{E2F93146-AB82-4522-8D83-15D8F23CC4FC}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/我的电脑/main.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[10].destinationIndex" Type="Int">3</Property>
				<Property Name="Source[10].itemID" Type="Ref">/我的电脑/Datas/测试波形S15_4.21_5(较满意_3).tdms_index</Property>
				<Property Name="Source[11].destinationIndex" Type="Int">4</Property>
				<Property Name="Source[11].itemID" Type="Ref">/我的电脑/Docs/Ecan动态库使用手册5.2.pdf</Property>
				<Property Name="Source[12].destinationIndex" Type="Int">4</Property>
				<Property Name="Source[12].itemID" Type="Ref">/我的电脑/Docs/驱动安装说明.pdf</Property>
				<Property Name="Source[13].destinationIndex" Type="Int">4</Property>
				<Property Name="Source[13].itemID" Type="Ref">/我的电脑/Docs/修改日志.txt</Property>
				<Property Name="Source[14].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[14].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[14].destinationIndex" Type="Int">5</Property>
				<Property Name="Source[14].itemID" Type="Ref">/我的电脑/Drivers/GC</Property>
				<Property Name="Source[14].type" Type="Str">Container</Property>
				<Property Name="Source[15].destinationIndex" Type="Int">1</Property>
				<Property Name="Source[15].itemID" Type="Ref">/我的电脑/SysInit/上传序列.dat</Property>
				<Property Name="Source[2].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[2].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/我的电脑/Confs</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">Container</Property>
				<Property Name="Source[3].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[3].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">2</Property>
				<Property Name="Source[3].itemID" Type="Ref">/我的电脑/Confs/Receive</Property>
				<Property Name="Source[3].type" Type="Str">Container</Property>
				<Property Name="Source[4].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[4].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">2</Property>
				<Property Name="Source[4].itemID" Type="Ref">/我的电脑/Confs/Send</Property>
				<Property Name="Source[4].type" Type="Str">Container</Property>
				<Property Name="Source[5].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[5].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/我的电脑/Datas</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">Container</Property>
				<Property Name="Source[6].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[6].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/我的电脑/Docs</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">Container</Property>
				<Property Name="Source[7].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[7].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[7].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[7].itemID" Type="Ref">/我的电脑/Drivers</Property>
				<Property Name="Source[7].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[7].type" Type="Str">Container</Property>
				<Property Name="Source[8].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[8].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[8].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[8].itemID" Type="Ref">/我的电脑/SysInit</Property>
				<Property Name="Source[8].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[8].type" Type="Str">Container</Property>
				<Property Name="Source[9].destinationIndex" Type="Int">3</Property>
				<Property Name="Source[9].itemID" Type="Ref">/我的电脑/Datas/测试波形S15_4.21_5(较满意_3).tdms</Property>
				<Property Name="SourceCount" Type="Int">16</Property>
				<Property Name="TgtF_companyName" Type="Str">work for myself</Property>
				<Property Name="TgtF_fileDescription" Type="Str">我的应用程序</Property>
				<Property Name="TgtF_internalName" Type="Str">我的应用程序</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">版权 2018 work for myself</Property>
				<Property Name="TgtF_productName" Type="Str">我的应用程序</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{9D621557-7868-45D7-A6B5-F257C96E2A52}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">应用程序.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
