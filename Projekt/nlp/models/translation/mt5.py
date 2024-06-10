import sys
from transformers import pipeline

def mt5_translate(srcLanguage, dstLanguage, model, data):
  translator = pipeline("translation_" + srcLanguage + "_to_" + dstLanguage, model=model)
  output = translator(data)
  return output[0]['translation_text']

# print(mt5_translate("en", "pl", "sdadas/mt5-base-translator-en-pl", "I love pizza!"))
print(mt5_translate(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]))