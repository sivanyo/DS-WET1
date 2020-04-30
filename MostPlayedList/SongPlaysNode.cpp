////
//// Created by Mor on 27/04/2020.
////
//
//#include "SongPlaysNode.h"
//
//SongPlays::SongPlays(int songId, int artistId, shared_ptr<MostPlayedListNode> ptrToList) {
//
//}
//
//
////SongPlays::SongPlays(int songId, int artistId, shared_ptr<MostPlayedListNode> ptrToList) {
////    this->songId = songId;
////    this->numberOfPlays = 0;
////    this->artistId = artistId;
////    this->ptrToListNode = ptrToList;
////}
//
//int SongPlays::GetSongId() const {
//    return songId;
//}
//
//int SongPlays::GetNumberOfPlays() const {
//    return numberOfPlays;
//}
//
//int SongPlays::GetArtistId() const {
//    return artistId;
//}
//
//void SongPlays::IncrementNumberOfPlays() {
//    this->numberOfPlays++;
//}
//
//shared_ptr<MostPlayedListNode> SongPlays::GetPtrToListNode() {
//    return this->ptrToListNode;
//}
//
//void SongPlays::SetPtrToListNode(shared_ptr<MostPlayedListNode> listNode) {
//    this->ptrToListNode = listNode;
//}