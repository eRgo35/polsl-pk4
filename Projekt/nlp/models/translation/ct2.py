import sys

import ctranslate2
from sentencepiece import SentencePieceProcessor
from huggingface_hub import snapshot_download

def ct2_translate(dstLanguage, data):
    model_name = "santhosh/madlad400-3b-ct2"
    model_path = snapshot_download(model_name)

    tokenizer = SentencePieceProcessor()
    tokenizer.load(f"{model_path}/sentencepiece.model")
    translator = ctranslate2.Translator(model_path)

    input_tokens = tokenizer.encode(f"<2{dstLanguage}> {data}", out_type=str)
    results = translator.translate_batch(
        [input_tokens],
        batch_type="tokens",
        max_batch_size=1024,
        beam_size=1,
        no_repeat_ngram_size=1,
        repetition_penalty=2,
    )
    translated_sentence = tokenizer.decode(results[0].hypotheses[0])
    return translated_sentence

print(ct2_translate(sys.argv[1], sys.argv[2]))
# print(ct2_translate("it", "I love pizza!"))

