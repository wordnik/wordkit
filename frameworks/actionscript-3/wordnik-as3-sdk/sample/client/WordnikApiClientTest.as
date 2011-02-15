package client
{
import com.wordnik.api.batch.Batch;
import com.wordnik.api.batch.OpGetDefinitions;
import com.wordnik.api.batch.OpGetExamples;
import com.wordnik.api.batch.OpGetFrequencyData;
import com.wordnik.api.batch.OpGetPhrases;
import com.wordnik.api.batch.OpGetPronunciations;
import com.wordnik.api.batch.OpGetPunctuationFactor;
import com.wordnik.api.batch.OpGetRelatedWords;
import com.wordnik.api.client.WordnikClient;
import com.wordnik.api.entity.ApiTokenStatus;
import com.wordnik.api.entity.ApiUserCredentials;
import com.wordnik.api.entity.AuthenticationToken;
import com.wordnik.api.entity.AutoCompleteResult;
import com.wordnik.api.entity.SearchResult;
import com.wordnik.api.entity.Word;
import com.wordnik.api.entity.WordCount;
import com.wordnik.api.entity.WordOfTheDay;
import com.wordnik.api.entity.word.RelatedWordSet;
import com.wordnik.api.entity.word.TextPronunciation;
import com.wordnik.api.entity.word.UsageFrequency;
import com.wordnik.api.entity.word.WordDefinition;
import com.wordnik.api.entity.word.WordExample;
import com.wordnik.api.event.ApiClientEvent;
import com.wordnik.api.event.Response;
import com.wordnik.api.request.AutoCompleteRequest;

import flash.events.EventDispatcher;

import flexunit.framework.TestCase;


public class WordnikApiClientTest extends TestCase
{
	private static const TIME_OUT: Number = 20000;
    private var wordnikEventDispatcher: EventDispatcher;
    private var wordnikCredentials: ApiUserCredentials;
    private var wordnikClient: WordnikClient;
	public static const userName:String = Credentials.userName;
	public static const password:String = Credentials.password;
	public static const apiToken:String = Credentials.apiToken;

	public static const apiHostName:String = SDKTestApp.apiHostName;
	public var userId:int;

    public function WordnikApiClientTest(methodName:String=null)
    {
        super(methodName);
    }

    override public function setUp():void
    {
        wordnikCredentials = new ApiUserCredentials(apiToken,
                null, apiHostName, userId);
        super.setUp();
        wordnikEventDispatcher = new EventDispatcher();
        wordnikClient = new WordnikClient(wordnikCredentials, wordnikEventDispatcher);
        wordnikClient.useProxyServer(SDKTestApp.useApiProxyServer);
    }

    override public function tearDown():void
    {
        super.tearDown();
        wordnikEventDispatcher = null;
    }

    public function testWordLookUp():void{
        var requestId: String = wordnikClient.lookupWord("Dracula");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.WORD_LOOK_UP_COMPLETE_EVENT,
                addAsync(onWordRequestCompleted, TIME_OUT, requestId, timeOutHandler));

    }

    public function testWordSpellingSuggestions():void {
        var requestId: String = wordnikClient.getSpellingSuggestions("Zeebra");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.SUGGESTIONS_RESPONSE_EVENT,
                addAsync(onWordSuggestion, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testWordSuggestionsNonLiteral():void {
        var requestId: String = wordnikClient.getSpellingSuggestions("Zeebra", false);
        wordnikEventDispatcher.addEventListener(ApiClientEvent.SUGGESTIONS_RESPONSE_EVENT,
                addAsync(onWordSuggestionNonLiteral, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testWordRequestWithDefinition():void{
        var requestId: String = wordnikClient.getWordDefinitions("foo", 2, false, "noun");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.DEFINITIONS_RESPONSE_EVENT,
                addAsync(onWordDefinitionResponse, TIME_OUT, {requestId:requestId, partOfSpeech:"noun"} , timeOutHandler) );
    }

    public function testWordRequestWithExamples():void {
        var requestId: String = wordnikClient.getExampleSentences("cat");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.EXAMPLES_RESPONSE_EVENT,
                addAsync(onWordRequestWithExamples, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testWordRequestWithRelatedWords():void {
        var requestId: String = wordnikClient.getRelatedWords("abate");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.RELATED_WORDS_RESPONSE_EVENT,
                addAsync(onWordRequestWithRelated, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testWordRequestWithRelatedSynonyms():void {
        var requestId: String = wordnikClient.getRelatedWords("abate", 100, false, OpGetRelatedWords.PART_OF_SPEECH_ALL, "synonym");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.RELATED_WORDS_RESPONSE_EVENT,
                addAsync(onWordRequestWithRelatedSynonyms, TIME_OUT, requestId, timeOutHandler) );

    }

    public function testWordPronunciationRequest():void {
        var requestId: String = wordnikClient.getPronunciations("computer");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.PRONS_RESPONSE_EVENT,
                addAsync(onWordPronsResponse, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testWordFrequencyData():void {
        var requestId: String = wordnikClient.getFrequencyInfo("cat");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.FREQUENCY_INFO_RESPONSE_EVENT,
                addAsync(onWordFrequencyResponse, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testWordPunctuationFactor():void {
        var requestId: String = wordnikClient.getPunctuationFactor("cat");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.PUNCTUATION_FACTOR_RESPONSE_EVENT,
                addAsync(onWordPunctuationFactorResponse, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testWordAutoComplete():void {
        var requestId: String = wordnikClient.autoComplete("ca", 2);
        wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTO_COMPLETE_RESPONSE_EVENT,
                addAsync(onWordAutoCompleteResponse, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testAllElementRequests():void{
        const batch: Batch = new Batch();
        batch.add(new OpGetPhrases());
        batch.add(new OpGetDefinitions(2));
        batch.add(new OpGetExamples());
        batch.add(new OpGetRelatedWords());
        batch.add(new OpGetFrequencyData());
        batch.add(new OpGetPunctuationFactor());
        batch.add(new OpGetPronunciations());

		var requestId : String  = wordnikClient.execute("gargantuan", batch);
		wordnikEventDispatcher.addEventListener(ApiClientEvent.BATCH_EXECUTE_RESPONSE_EVENT,
                addAsync(onAllWordElementRequestCompleted, TIME_OUT, requestId, timeOutHandler) );
    }

    public function testWordOfTheDay():void{
        var requestId: String = wordnikClient.requestWordOfTheDay();
        wordnikEventDispatcher.addEventListener(ApiClientEvent.WORD_OF_DAY_RESPONSE_EVENT,
                addAsync(onWOTDRequestCompleted, TIME_OUT, requestId, timeOutHandler));
    }

    public function testRandomWord():void{
        var requestId: String = wordnikClient.requestRandomWord();
        wordnikEventDispatcher.addEventListener(ApiClientEvent.RANDOM_WORD_RESPONSE_EVENT,
                addAsync(onRandomWordRequestComplete, TIME_OUT, requestId, timeOutHandler));
    }

    public function testRandomWords():void{
        var requestId: String = wordnikClient.requestRandomWords(5);
        wordnikEventDispatcher.addEventListener(ApiClientEvent.RANDOM_WORDS_RESPONSE_EVENT,
                addAsync(onRandomWordsRequestCompleted, TIME_OUT, requestId, timeOutHandler));

    }

    public function testApiUsageInfo():void{
        var requestId: String = wordnikClient.requestApiUsageInfo();
        wordnikEventDispatcher.addEventListener(ApiClientEvent.API_USAGE_RESPONSE_EVENT,
                addAsync(onApiUsageInfoResponse, TIME_OUT, requestId, timeOutHandler));
    }

    public function testSearchWords():void{
        var requestId: String = wordnikClient.searchWords("c@@*p");
        wordnikEventDispatcher.addEventListener(ApiClientEvent.SEARCH_RESPONSE_EVENT,
                addAsync(onSearchWordsCompleted, TIME_OUT, requestId, timeOutHandler));
    }

    public function testAuthentication():void{
        var requestId: String = wordnikClient.authenticate(userName, password);

        wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTHENTICATION_RESPONSE_EVENT,
                addAsync( function(event: ApiClientEvent, requestId: String):void{
                    var result: Response = event.response;
                    assertDefaultResponseParams(result, requestId, AuthenticationToken);
                    var authenticationToken: AuthenticationToken = result.payload as AuthenticationToken;
                    assertTrue("testAuthentication: Authentication token cannot be empty", authenticationToken.token != null && authenticationToken.token != "");
                    assertTrue("testAuthentication: Authentication token userid cannot be empty", authenticationToken.userId != null && authenticationToken.userId != "");
                 } , TIME_OUT, requestId, timeOutHandler) );
    }


    private function onSearchWordsCompleted(event: ApiClientEvent, requestId: String):void {
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, SearchResult);
        var searchResult: SearchResult = result.payload as SearchResult;
        assertNotNull("Search result frequencies cannot be null",searchResult.wordFrequencies);
        assertTrue("Search result frequencies cannot be empty for the query c@@*p",searchResult.wordFrequencies.length > 0);
        assertTrue("Search result is not in expected WordCount format",searchResult.wordFrequencies[0] is WordCount);
        assertNotNull("Search result word cannot be null",WordCount(searchResult.wordFrequencies[0]).word);
        assertTrue("Search result word count cannot be null", !isNaN( WordCount(searchResult.wordFrequencies[0]).count) );
    }

    private function onWordRequestCompleted(event: ApiClientEvent, requestId: String):void {
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordnikWord: Word = result.payload as Word;
        //assertTrue("word result id cannot be empty", wordnikWord.id != null && wordnikWord.id != "" );
        assertTrue("word result word cannot be empty", wordnikWord.word != null && wordnikWord.word != "");
		assertTrue("word result canonical form cannot be empty", wordnikWord.canonicalForm != null && wordnikWord.canonicalForm != "");
        //assertTrue("word result suggestions should be empty for simple request", wordnikWord.suggestions == null || wordnikWord.suggestions.length == 0);
    }

    private function onWordSuggestion(event: ApiClientEvent, requestId: String):void {
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordnikWord: Word = result.payload as Word;
        //assertTrue("word result id cannot be empty", wordnikWord.id != null && wordnikWord.id != "" );
        assertTrue("word result word cannot be empty", wordnikWord.word != null && wordnikWord.word != "");
    }

    private function onWordSuggestionNonLiteral(event: ApiClientEvent, requestId: String):void {
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordnikWord: Word = result.payload as Word;
        //assertTrue("word result id cannot be empty", wordnikWord.id != null && wordnikWord.id != "" );
        assertTrue("word result word cannot be empty", wordnikWord.word != null && wordnikWord.word != "");
        //assertTrue("word result suggestions should be empty for non literal request", wordnikWord.suggestions == null || wordnikWord.suggestions.length == 0);
    }

    private function onApiUsageInfoResponse(event: ApiClientEvent, requestId: String):void {
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, ApiTokenStatus);
        var apiTokenStatus: ApiTokenStatus = result.payload as ApiTokenStatus;
        assertNotNull("Api token cannot be null",apiTokenStatus.token);
        assertNotNull("Api token status cannot be null",apiTokenStatus.isTokenValid);
        assertTrue("Api token: expiresInMillis cannot be NaN", !isNaN( apiTokenStatus.expiresInMillis ) );
        assertTrue("Api token: remainingCalls cannot be NaN", !isNaN( apiTokenStatus.remainingCalls ) );
        assertTrue("Api token: resetsInMillis cannot be NaN", !isNaN( apiTokenStatus.resetsInMillis ) );
        assertTrue("Api token: totalRequests cannot be NaN", !isNaN( apiTokenStatus.totalRequests ) );
    }

    private function onRandomWordsRequestCompleted(event: ApiClientEvent, requestId: String):void {
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Array);
        var randomWords: Array = result.payload as Array;

        assertTrue("Random words result list cannot be empty", randomWords.length > 0);
        assertNotNull("Random word result: element is not a Word", randomWords[0] is Word);
        for each(var randomword: Word in randomWords) {
            //assertNotNull("Random word result: id cannot be null", randomword.id);
            //assertTrue("Random word result: id cannot be null", randomword.id != "");

            assertNotNull("Random word result: word cannot be null", randomword.word);
        }
    }

    private function onRandomWordRequestComplete(event: ApiClientEvent, requestId: String):void {
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var randomWord: Word = result.payload as Word;
        //assertNotNull("Random word result id cannot be null", randomWord.id);
        assertNotNull("Random word result word cannot be null", randomWord.word);
    }

    private function onWOTDRequestCompleted(event: ApiClientEvent, requestId: String):void {
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, WordOfTheDay);
        var wordOfTheDay: WordOfTheDay = result.payload as WordOfTheDay;
        assertNotNull("Word of the day word cannot be null",wordOfTheDay.wordString);
        assertNotNull("Word of the day publish date cannot be null",wordOfTheDay.publishDate);
        assertNotNull("Word of the day id cannot be null",wordOfTheDay.id);
        assertNotNull("Word of the day definitions cannot be null",wordOfTheDay.definitions);
        assertTrue("Word of the day definitions cannot be empty",wordOfTheDay.definitions.length > 0);
        assertTrue("Word of the day examples cannot be empty",wordOfTheDay.examples.length > 0);
    }

    private function onAllWordElementRequestCompleted(event: ApiClientEvent, requestId: String):void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        //TODO - check for elements if elements requested 
    }

    private function onWordRequestWithExamples(event: ApiClientEvent, requestId: String): void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordResult: Word = result.payload as Word;
        checkForExamples(wordResult);
    }

    private function onWordDefinitionResponse(event: ApiClientEvent, tokenObject: Object): void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, tokenObject.requestId, Word);
        var wordResult: Word = result.payload as Word;
        checkForDefinitions(wordResult, tokenObject.partOfSpeech);
    }

    private function onWordRequestWithRelated(event: ApiClientEvent, requestId: String): void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordResult: Word = result.payload as Word;
        checkForRelatedWords(wordResult);
    }

    private function onWordRequestWithRelatedSynonyms(event: ApiClientEvent, requestId: String): void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordResult: Word = result.payload as Word;
        checkForRelatedWordsWithType(wordResult, "synonym");
    }

    private function onWordPronsResponse(event: ApiClientEvent, requestId: String): void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordResult: Word = result.payload as Word;
        checkForTextProns(wordResult);
    }

    private function checkForTextProns(wordResult:Word):void {
        var textPron: TextPronunciation;
        for each(var textPronObj: Object in wordResult.textPronunciations){
            assertTrue("Text pronunciation result element should be WNTextPron", textPronObj != null && textPronObj is TextPronunciation);
            textPron = TextPronunciation(textPronObj);
            assertTrue("Text pronunciation raw string cannot be empty", textPron.raw != null && textPron.raw != "");
            assertTrue("Text pronunciation raw type cannot be empty", textPron.rawType != null && textPron.rawType != "");
        }
    }

    private function onWordFrequencyResponse(event: ApiClientEvent, requestId: String): void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordResult: Word = result.payload as Word;
        checkForFrequencySummary(wordResult);
    }

    private function onWordPunctuationFactorResponse(event: ApiClientEvent, requestId: String): void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, Word);
        var wordResult: Word = result.payload as Word;
        checkForPunctuationFactor(wordResult);
    }

    private function onWordAutoCompleteResponse(event: ApiClientEvent, requestId: String): void{
        var result: Response = event.response;
        assertDefaultResponseParams(result, requestId, AutoCompleteResult);
        var aWNAutoCompleteResult: AutoCompleteResult = result.payload as AutoCompleteResult;
        assertTrue("Auto complete result has no matches", aWNAutoCompleteResult.matches > 0);
        assertTrue("Auto complete result has no match results", aWNAutoCompleteResult.searchResults.length > 0);
        assertTrue("Auto complete result should not exceed limit", aWNAutoCompleteResult.searchResults.length <= 3);
        var requestSearchFragment: String = requestId;
        for each(var matchResult: WordCount in aWNAutoCompleteResult.searchResults){
            assertTrue("Auto complete match result element cannot have empty wordstring", matchResult.word != "");
        }
        assertTrue("Auto complete search term match word should match requested fragment", aWNAutoCompleteResult.fragmentSearchResult.word = requestSearchFragment);
    }

    private function checkForPunctuationFactor(wordResult:Word):void {
        assertTrue("Word punctuation factor word id cannot be empty" ,wordResult.punctuationFactor.wordId != null && wordResult.punctuationFactor.wordId != "");
        assertTrue("Word punctuation factor word id totalCount should be > 0" ,wordResult.punctuationFactor.totalCount >0);
        assertTrue("Word punctuation factor word id exclamationPointCount cannot be NaN" , !isNaN(wordResult.punctuationFactor.exclamationPointCount));
        assertTrue("Word punctuation factor word id periodCount cannot be NaN" , !isNaN(wordResult.punctuationFactor.periodCount));
        assertTrue("Word punctuation factor word id questionMarkCount cannot be NaN" , !isNaN(wordResult.punctuationFactor.questionMarkCount));
    }

    private function checkForFrequencySummary(wordResult:Word):void {
        assertTrue("Word result should contain atleast one frequency data elment when element was requested", wordResult.frequencyData.usageFrequencies.length > 0);
        assertTrue("Word in frequency summary cannot be empty", wordResult.frequencyData.word != null && wordResult.frequencyData.word != "");
        for each(var usageFrequencyElement: UsageFrequency in wordResult.frequencyData.usageFrequencies){
            assertTrue("Usage frequency info should have a valid count and year", usageFrequencyElement.count > -1 && usageFrequencyElement.year > 0);
        }
    }

    private function checkForRelatedWords(wordResult:Word):void {
        assertTrue("Word result should contain related words when element was requested", wordResult.relatedWords.length > 0);
        for each(var aWNRelatedWordSet: RelatedWordSet in wordResult.relatedWords){
            assertTrue("Related word should have a relation type", aWNRelatedWordSet.relationType != null && aWNRelatedWordSet.relationType != "");
            assertTrue("Related word should have atleast one wordstring for a relation  type", aWNRelatedWordSet.words != null && aWNRelatedWordSet.words.length > 0);
            for each(var relatedWord: String in aWNRelatedWordSet.words){
                assertTrue("Related word wordString should be a valid String value", relatedWord != null && relatedWord != "");
            }
        }
    }

    private function checkForRelatedWordsWithType(wordResult:Word, relType: String):void {
        assertFalse("word result should ony contain one related word set for "+relType, wordResult.relatedWords.length > 1);
        for each(var aWNRelatedWordSet: RelatedWordSet in wordResult.relatedWords){
            assertTrue("Related word type should be "+relType , aWNRelatedWordSet.relationType != null && aWNRelatedWordSet.relationType != "" && aWNRelatedWordSet.relationType == relType);
            assertTrue("Related word should have atleast one wordstring for a relation  type", aWNRelatedWordSet.words != null && aWNRelatedWordSet.words.length > 0);
            for each(var relatedWord: String in aWNRelatedWordSet.words){
                assertTrue("Related word wordString should be a valid String value", relatedWord != null && relatedWord != "");
            }
        }
    }

    private function checkForExamples(wordResult:Word):void {
        assertTrue("word result should contain examples when element was requested", wordResult.examples.length > 0);
        for each(var example:WordExample in wordResult.examples) {
            assertTrue("word example display value cannot be empty", example.display != null && example.display != "");
        }
    }

    private function checkForDefinitions(wordResult:Word, pos:String = null):void {
        assertTrue("word result should contain definitions when element was requested", wordResult.definitions.length > 0);
        assertTrue("word result should contain definitions lesser than limit", wordResult.definitions.length < 3);
        var definition: WordDefinition;
        for each(var defnObj:Object in wordResult.definitions) {
            assertTrue("Word definition array element should be a WordDefinition", defnObj != null && defnObj is WordDefinition);
            definition = WordDefinition(defnObj);
            assertTrue("Word definition sequence value cannot be empty", definition.sequence != null && definition.sequence != "");
            assertTrue("Word definition word value cannot be empty", definition.word != null && definition.word != "");
            assertTrue("Word definition partOfSpeech value cannot be empty", definition.partOfSpeech != null && definition.partOfSpeech != "");
            if (pos != null && pos!= "") {
                assertTrue("Word definition partOfSpeech value should be as per request", definition.partOfSpeech == pos);
            }
        }
    }

    private function assertDefaultResponseParams(result:Response, requestId: String,
												 resultClass: Class):void {
		assertTrue("Error response: "+ result.errorMessage, result.isSuccess);
		assertTrue("unknown payload object in response", result.payload is resultClass);
        assertTrue("requestId does not match what was used on invocation ", result.requestId == requestId);
    }

    private function timeOutHandler(o: Object):void {
        fail("test timed out");
    }
}
}