// hello.cc
#include <node.h>

using namespace v8;

void Method(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.Length() < 2)
  {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
    return;
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber())
  {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
    return;
  }

  double value = args[0]->NumberValue(isolate->GetCurrentContext()).FromJust() + args[1]->NumberValue(isolate->GetCurrentContext()).FromJust();
  Local<Number> num = Number::New(isolate, value);

  args.GetReturnValue().Set(num);
}

void Initialize(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "myCusttomFunc", Method);
};

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)