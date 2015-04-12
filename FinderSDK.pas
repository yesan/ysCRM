unit FinderSDK;

interface
uses
  Windows;


const
  FinderLibName = 'finderlib.dll';

  ERR_OK = 0;
  ERR_TIMEOUT = 1;
  ERR_FINDER_NOT_RUN = 2;
  ERR_COMM = 3;
  ERR_FINDER_VER = 4;
  ERR_FINDER_NOT_INSTALLED = 9;
  ERR_FINDER_INITIALIZING = 10;
  ERR_UNKNOWN = 99;  
type
  TResultCallBackA = procedure(Buffer: PPAnsiChar; BufferCount: Integer; TotalCount: Integer;
    ErrorCode: Integer); stdcall;
  TResultCallBackW = procedure(Buffer: System.PPWideChar; BufferCount: Integer; TotalCount: Integer;
    ErrorCode: Integer); stdcall;

  TResultCallBack = procedure(Buffer: System.PPChar; BufferCount: Integer; TotalCount: Integer;
    ErrorCode: Integer); stdcall;

function LaunchFinder: Boolean; stdcall;external FinderLibName;
function IsFinderRunning: Boolean; stdcall; external FinderLibName;

function CheckRequirement: Integer; stdcall;external FinderLibName;

function FindA(const AStr: PAnsiChar;
const ACallback: TResultCallBackA;
  const ADir, AExcludeDir, AFilter: PAnsiChar;
  const ACount: Integer = 100;
  const Afrom: Integer = 0;
  const ASpaceOr: Boolean = False;
  const AWholeWords: Boolean = False;
  const ACaseSensitive: Boolean = False;
  const AIncludeDir: Boolean = True;
  const AIncludeFiles: Boolean = True;
  const ATimeoutMS: Word = 1000)
  : Integer; stdcall; external FinderLibName;

function FindW(const AStr: PWideChar;
const ACallback: TResultCallBackW;
  const ADir, AExcludeDir, AFilter: PWideChar;
  const ACount: Integer = 100;
  const Afrom: Integer = 0;
  const ASpaceOr: Boolean = False;
  const AWholeWords: Boolean = False;
  const ACaseSensitive: Boolean = False;
  const AIncludeDir: Boolean = True;
  const AIncludeFiles: Boolean = True;
  const ATimeoutMS: Word = 1000)
  : Integer; stdcall; external FinderLibName;

function Find(const AStr: PChar;
const ACallback: TResultCallBackW;
  const ADir, AExcludeDir, AFilter: PChar;
  const ACount: Integer = 100;
  const Afrom: Integer = 0;
  const ASpaceOr: Boolean = False;
  const AWholeWords: Boolean = False;
  const ACaseSensitive: Boolean = False;
  const AIncludeDir: Boolean = True;
  const AIncludeFiles: Boolean = True;
  const ATimeoutMS: Word = 1000)
  : Integer; stdcall; external FinderLibName name {$IFDEF UNICODE}'FindW'{$ELSE}'FindA'{$ENDIF};

implementation

end.
