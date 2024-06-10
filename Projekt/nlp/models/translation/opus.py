import sys
from transformers import pipeline

def opus_translate(srcLanguage, dstLanguage, model, data):
  translator = pipeline("translation_" + srcLanguage + "_to_" + dstLanguage, model=model)
  output = translator(data)
  return output[0]['translation_text']

# print(opus_translate("en", "pl", "jproboszcz/opus-mt-en-pl", "I love pizza!"))
print(opus_translate(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]))