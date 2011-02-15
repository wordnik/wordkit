package client
{
	import com.wordnik.api.client.WordnikClient;
	import com.wordnik.api.entity.ApiUserCredentials;
	import com.wordnik.api.entity.AuthenticationToken;
	import com.wordnik.api.entity.WordList;
	import com.wordnik.api.event.ApiClientEvent;
	import com.wordnik.api.event.Response;
	
	import flash.events.EventDispatcher;
	
	import flexunit.framework.TestCase;
	
	public class WordnikListTests extends TestCase
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
		public var currentListName: String;

		public function WordnikListTests(methodName:String=null)
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
            cleanUpUserTestList();
		}

        private function cleanUpUserTestList():void {
			var requestId: String = wordnikClient.authenticate(userName, password);
            wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTHENTICATION_RESPONSE_EVENT,
                     function(event: ApiClientEvent):void{
                        var result: Response = event.response;
                        if(!result.payload is AuthenticationToken){
                            fail("Authenication token could not be retrieved");
                        }
                        var authenticationToken: AuthenticationToken = result.payload as AuthenticationToken;
                        wordnikClient.authenticationToken = authenticationToken;
                        var requestId2: String =  wordnikClient.requestUserLists();
                        wordnikEventDispatcher.addEventListener(ApiClientEvent.GET_USER_LISTS_RESPONSE_EVENT,
                                onUserListsRetrievedForCleanup);
                    }  );

        }

        private function  onUserListsRetrievedForCleanup(event: ApiClientEvent): void{
            var result: Response = event.response;
			var userLists: Array = result.payload as Array;
			for each(var wordList: WordList in userLists){
                if(wordList.name == currentListName) {
                    wordnikClient.deleteUserList(wordList.permalink);
                }
				wordnikEventDispatcher = null;
				//assertTrue("Wordlist word username cannot be empty", wordList.userName != null && wordList.userName != "" );
			}
        }

		public function testGetUserLists():void{
			var requestId: String = wordnikClient.authenticate(userName, password);
            wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTHENTICATION_RESPONSE_EVENT,
                    addAsync( function(event: ApiClientEvent, requestId: String):void{
                        var result: Response = event.response;
                        if(!result.payload is AuthenticationToken){
                            fail("Authenication token could not be retrieved");
                        }
                        var authenticationToken: AuthenticationToken = result.payload as AuthenticationToken;
                        wordnikClient.authenticationToken = authenticationToken;
                        var requestId2: String =  wordnikClient.requestUserLists();
                        wordnikEventDispatcher.addEventListener(ApiClientEvent.GET_USER_LISTS_RESPONSE_EVENT,
                                addAsync(onUserListsResponse, TIME_OUT, requestId2, timeOutHandler));
                    } , TIME_OUT, requestId, timeOutHandler) );
			
		}
		
		public function testCreateUserList():void{
			var requestId: String = wordnikClient.authenticate(userName, password);
            wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTHENTICATION_RESPONSE_EVENT,
                    addAsync( function(event: ApiClientEvent, requestId: String):void{
                        var result: Response = event.response;

                        if(!result.payload is AuthenticationToken){
                            fail("Authenication token could not be retrieved");
                        }
                        var authenticationToken: AuthenticationToken = result.payload as AuthenticationToken;
                        wordnikClient.authenticationToken = authenticationToken;
                        var requestId2: String =  wordnikClient.createUserList("testCreateUserList", "desctestCreateUserList");
                        currentListName = "testCreateUserList";
                        wordnikEventDispatcher.addEventListener(ApiClientEvent.CREATE_LIST_RESPONSE_EVENT,
                                addAsync(onUserListCreated, TIME_OUT, requestId2, timeOutHandler));
                    } , TIME_OUT, requestId, timeOutHandler) );
			
		}
		
		public function testDeleteUserList():void{
			var requestId: String = wordnikClient.authenticate(userName, password );
            wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTHENTICATION_RESPONSE_EVENT,
                    addAsync( function(event: ApiClientEvent, requestId: String):void{
                        var result: Response = event.response;
                        if(!result.payload is AuthenticationToken){
                            fail("Authenication token could not be retrieved");
                        }
                        var authenticationToken: AuthenticationToken = result.payload as AuthenticationToken;
                        wordnikClient.authenticationToken = authenticationToken;
                        var creationRequestID: String = wordnikClient.createUserList("deleteTestUserList", "testingDeleteUserList");
                        currentListName = "deleteTestUserList";
                        wordnikEventDispatcher.addEventListener(ApiClientEvent.CREATE_LIST_RESPONSE_EVENT,
                                addAsync(
                                function(event: ApiClientEvent, requestId: String):void{
                                    var result: Response = event.response;
                                    if(!result.payload is WordList || WordList(result.payload).permalink == null || WordList(result.payload).permalink == ""){
                                        fail("Wordlist could not be retrieved");
                                    }
                                    var wordList: WordList = result.payload as WordList;
                                    var deleteRequestId: String = wordnikClient.deleteUserList(wordList.permalink);
                                    wordnikEventDispatcher.addEventListener(ApiClientEvent.DELETE_LIST_REPOSNSE_EVENT,
                                            addAsync(onUserListDeleted, TIME_OUT, deleteRequestId, timeOutHandler));
                                } , TIME_OUT, creationRequestID, timeOutHandler));
                    } , TIME_OUT, requestId, timeOutHandler) );
			
		}
		
		public function testAddWordsToList():void{
			//wordnikClient.authenticate(userName, password, "testAuthentication", addAsync( function(result: Response, requestId: String):void{
			var requestId: String = wordnikClient.authenticate(userName, password );
            wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTHENTICATION_RESPONSE_EVENT,
                    addAsync( function(event: ApiClientEvent, requestId: String):void{
                        var result: Response = event.response;
                        if(!result.payload is AuthenticationToken){
                            fail("Authenication token could not be retrieved");
                        }
                        var authenticationToken: AuthenticationToken = result.payload as AuthenticationToken;
                        wordnikClient.authenticationToken = authenticationToken;
                        var creationRequestID: String = wordnikClient.createUserList("testAddWordsToList", "desctestCreateUserList");
                        currentListName = "testAddWordsToList";
                        wordnikEventDispatcher.addEventListener(ApiClientEvent.CREATE_LIST_RESPONSE_EVENT,
                                addAsync(
                                function(event: ApiClientEvent, requestId: String):void{
                                    var result: Response = event.response;
                                    if(!result.payload is WordList || WordList(result.payload).permalink == null || WordList(result.payload).permalink == ""){
                                        fail("Wordlist could not be retrieved");
                                    }
                                    var wordList: WordList = result.payload as WordList;
                                    var addWordsRequestId : String = wordnikClient.addWordsToList(wordList.permalink, ["api", "test","add","words","to","list"]);
                                    wordnikEventDispatcher.addEventListener(ApiClientEvent.ADD_WORDS_RESPONSE_EVENT,
                                            addAsync(onWordsAddedToList, TIME_OUT, addWordsRequestId, timeOutHandler));
                                } , TIME_OUT, creationRequestID, timeOutHandler));
                    } , TIME_OUT, requestId, timeOutHandler) );
			
		}
		
		public function testGetWordsFromList():void{
			var requestId: String = wordnikClient.authenticate(userName, password );
			wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTHENTICATION_RESPONSE_EVENT,
				addAsync( function(event: ApiClientEvent, requestId: String):void{
					var result: Response = event.response;
					if(!result.payload is AuthenticationToken){
						fail("Authenication token could not be retrieved");
					}
					var authenticationToken: AuthenticationToken = result.payload as AuthenticationToken;
					wordnikClient.authenticationToken = authenticationToken;
					var creationRequestID: String = wordnikClient.createUserList("testGetWordsFromList", "desctestCreateUserList");
                    currentListName = "testGetWordsFromList";
					wordnikEventDispatcher.addEventListener(ApiClientEvent.CREATE_LIST_RESPONSE_EVENT,
						addAsync(
							function(event: ApiClientEvent, requestId: String):void{
								var result: Response = event.response;
								if(!result.payload is WordList || WordList(result.payload).permalink == null || WordList(result.payload).permalink == ""){
									fail("Wordlist could not be retrieved");
								}
								//add words to delete later
								var wordList: WordList = result.payload as WordList;
								var addWordsRequestId : String = wordnikClient.addWordsToList(wordList.permalink, ["api", "test"]);
								wordnikEventDispatcher.addEventListener(ApiClientEvent.ADD_WORDS_RESPONSE_EVENT,
									addAsync(
										function (event: ApiClientEvent, tokenObject: Object): void{
											var result: Response = event.response;
											assertTrue("Word lists could not be added to list to test retrieve: "+ result.errorMessage , result.isSuccess);
											var getWordsRequestId : String = wordnikClient.getWordsFromList(tokenObject.permalink);
											wordnikEventDispatcher.addEventListener(ApiClientEvent.GET_LIST_WORDS_RESPONSE_EVENT,
												addAsync(onWordsRetrievedFromList, TIME_OUT, getWordsRequestId, timeOutHandler));
											
										}
										, TIME_OUT, {requestId:addWordsRequestId, permalink: wordList.permalink}, timeOutHandler));
							} , TIME_OUT, creationRequestID, timeOutHandler));
				} , TIME_OUT, requestId, timeOutHandler) );			
		}
		
		public function testDeleteWordsFromList():void{
			var requestId: String = wordnikClient.authenticate(userName, password );
            wordnikEventDispatcher.addEventListener(ApiClientEvent.AUTHENTICATION_RESPONSE_EVENT,
                    addAsync( function(event: ApiClientEvent, requestId: String):void{
                        var result: Response = event.response;
                        if(!result.payload is AuthenticationToken){
                            fail("Authenication token could not be retrieved");
                        }
                        var authenticationToken: AuthenticationToken = result.payload as AuthenticationToken;
                        wordnikClient.authenticationToken = authenticationToken;
                        var creationRequestID: String = wordnikClient.createUserList("testDeleteWordsFromList", "desctestCreateUserList");
                        currentListName = "testDeleteWordsFromList";
                        wordnikEventDispatcher.addEventListener(ApiClientEvent.CREATE_LIST_RESPONSE_EVENT,
                                addAsync(
                                function(event: ApiClientEvent, requestId: String):void{
                                    var result: Response = event.response;
                                    if(!result.payload is WordList || WordList(result.payload).permalink == null || WordList(result.payload).permalink == ""){
                                        fail("Wordlist could not be retrieved");
                                    }
                                    //add words to delete later
                                    var wordList: WordList = result.payload as WordList;
							        var addWordsRequestId : String = wordnikClient.addWordsToList(wordList.permalink, ["api", "test"]);
								    wordnikEventDispatcher.addEventListener(ApiClientEvent.ADD_WORDS_RESPONSE_EVENT,
                                            addAsync(
                                                    function (event: ApiClientEvent, tokenObject: Object): void{
                                                        var result: Response = event.response;
														assertTrue("Word lists could not be added to list to test delete: "+ result.errorMessage , result.isSuccess);
                                                        var delWordsRequestId : String = wordnikClient.deleteWordsFromList(tokenObject.permalink, ["api", "test"]);
                                                        wordnikEventDispatcher.addEventListener(ApiClientEvent.DELETE_WORDS_RESPONSE_EVENT,
                                                                addAsync(onWordsDeletedFromList, TIME_OUT, delWordsRequestId, timeOutHandler));

                                                    }
                                                    , TIME_OUT, {requestId:addWordsRequestId, permalink: wordList.permalink}, timeOutHandler));
						} , TIME_OUT, creationRequestID, timeOutHandler));
			} , TIME_OUT, requestId, timeOutHandler) );
			
		}
		
		private function onWordsDeletedFromList(event: ApiClientEvent, requestId: String):void {
            var result: Response = event.response;
			assertTrue("Word lists were not deleted from list : "+ result.errorMessage , result.isSuccess);
		}
		
		private function onWordsRetrievedFromList(event: ApiClientEvent, requuestId: String): void {
			var result: Response = event.response;
			assertTrue("Word list words were not retrieved from list : "+ result.errorMessage , result.isSuccess);
		}
		
		private function onWordsAddedToList(event: ApiClientEvent, requestId: String):void {
            var result: Response = event.response;
			assertTrue("Word lists were not added to list : "+ result.errorMessage , result.isSuccess);
		}
		
		private function onUserListDeleted(event: ApiClientEvent, requestId: String):void {
            var result: Response = event.response;
            assertTrue("User list deletion was unsuccesful",result.isSuccess);
		}
		
		private function onUserListCreated(event: ApiClientEvent, requestId: String):void {
            var result: Response = event.response;
            assertDefaultResponseParams(result, requestId, WordList);
			var wordList: WordList = result.payload as WordList;
			assertTrue("Wordlist word name does not match requested", wordList.name != null && wordList.name == "testCreateUserList" );
			assertTrue("Wordlist word description does not match requested", wordList.description != null && wordList.description == "desctestCreateUserList"  );
			assertTrue("Wordlist permalink cannot be empty", wordList.permalink != null );
			//assertTrue("Wordlist word username cannot be empty", wordList.userName != null && wordList.userName != "" );
			
		}
		
		private function onUserListsResponse(event: ApiClientEvent, requestId: String):void {
            var result: Response = event.response;
			assertDefaultResponseParams(result, requestId, Array);
			var userLists: Array = result.payload as Array;
			for each(var wordList: WordList in userLists){
				assertTrue("Wordlist word name cannot be empty", wordList.name != null && wordList.name != "" );
				assertTrue("Wordlist word id cannot be empty", wordList.id != null && wordList.id != "" );
				assertTrue("Wordlist permalink cannot be empty", wordList.permalink != null && wordList.permalink != "" );
				//assertTrue("Wordlist word username cannot be empty", wordList.userName != null && wordList.userName != "" );
			}
			
		}
		
		private function assertDefaultResponseParams(result:Response, requestId: String,
													 resultClass: Class):void {
			assertTrue("Response message is not a success message", result.isSuccess);
			assertTrue("unknown payload object in response", result.payload is resultClass);
			assertTrue("requestId does not match what was used on invocation ", result.requestId == requestId);
		}
		
		private function timeOutHandler(o: Object):void {
			fail("test timed out");
		}
		
	
	}
}