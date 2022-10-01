pushd %~dp0
protoc.exe -I=./ --cpp_out=./ ./Enum.proto
protoc.exe -I=./ --cpp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ ./Protocol.proto

IF ERRORLEVEL 1 PAUSE

XCOPY /Y Enum.pb.h "../../GameServer"
XCOPY /Y Enum.pb.cc "../../GameServer"
XCOPY /Y Struct.pb.h "../../GameServer"
XCOPY /Y Struct.pb.cc "../../GameServer"
XCOPY /Y Protocol.pb.h "../../GameServer"
XCOPY /Y Protocol.pb.cc "../../GameServer"
XCOPY /Y ClientPacketHandler.h "../../GameServer"

XCOPY /Y Enum.pb.h "../../DummyClient"
XCOPY /Y Enum.pb.cc "../../DummyClient"
XCOPY /Y Struct.pb.h "../../DummyClient"
XCOPY /Y Struct.pb.cc "../../DummyClient"
XCOPY /Y Protocol.pb.h "../../DummyClient"
XCOPY /Y Protocol.pb.cc "../../DummyClient"
XCOPY /Y ServerPacketHandler.h "../../DummyClient"

XCOPY /Y Enum.pb.h "../../Pong"
XCOPY /Y Enum.pb.cc "../../Pong"
XCOPY /Y Struct.pb.h "../../Pong"
XCOPY /Y Struct.pb.cc "../../Pong"
XCOPY /Y Protocol.pb.h "../../Pong"
XCOPY /Y Protocol.pb.cc "../../Pong"
XCOPY /Y ServerPacketHandler.h "../../Pong"

XCOPY /Y Enum.pb.h "../../BreakoutServer"
XCOPY /Y Enum.pb.cc "../../BreakoutServer"
XCOPY /Y Struct.pb.h "../../BreakoutServer"
XCOPY /Y Struct.pb.cc "../../BreakoutServer"
XCOPY /Y Protocol.pb.h "../../BreakoutServer"
XCOPY /Y Protocol.pb.cc "../../BreakoutServer"
XCOPY /Y ServerPacketHandler.h "../../BreakoutServer"

PAUSE