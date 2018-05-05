#include <iostream>

template< typename TacKey, typename TacVal >
struct TacHashMap
{
  typedef int TacHashFn( TacKey key );
  struct TacNode
  {
    int mHash = 0;
    TacKey mKey = {};
    TacVal mVal = {};
    bool mOccupied = false;
  };
  ~TacHashMap()
  {
    delete[] mNodes;
  }
  TacHashMap()
  {
    mNodes = new TacNode[ mCapacity = 10 ];
  }
  void Remove( TacKey key )
  {
    TacNode* node = Find( key );
    *node = TacNode();
    int iEmpty = node - mNodes;
    int i = ( iEmpty + 1 ) % mCapacity;
    for( ;; )
    {
      node = &mNodes[ i ];
      if( !node->mOccupied )
        break;
      int iDesired = node->mHash % mCapacity;
      if( iDesired != i && iDesired <= iEmpty )
      {
        mNodes[ iEmpty ] = *node;
        *node = TacNode();
        iEmpty = i;
      }
      i = ( i + 1 ) % mCapacity;
    }
    --mSize;
  }
  TacNode* Find( TacKey key )
  {
    TacNode* node;
    int hash = mHashFn( key );
    int i = hash % mCapacity;
    for( ;; )
    {
      node = &mNodes[ i ];
      if( !node->mOccupied || ( node->mHash == hash && node->mKey == key ) )
        break;
      i = ( i + 1 ) % mCapacity;
    }
    return node;
  }
  bool Contains( TacKey key )
  {
    TacNode* node = Find( key );
    return node->mOccupied;
  }
  TacVal& operator[]( TacKey key )
  {
    TacNode* node = Find( key );
    if( !node->mOccupied )
    {
      if( mSize + 1 > mCapacity / 2 )
      {
        TacNode* oldNodes = mNodes;
        int oldCapacity = mCapacity;
        mNodes = new TacNode[ mCapacity = oldCapacity * 2 ];
        mSize = 0;
        for( int i = 0; i < oldCapacity; ++i )
        {
          TacNode* oldNode = &oldNodes[ i ];
          if( !oldNode->mOccupied )
            continue;
          TacVal& newVal = this->operator[]( oldNode->mKey );
          newVal = oldNode->mVal;
        }
        delete[] oldNodes;
        node = Find( key );
      }
      node->mOccupied = true;
      node->mHash = mHashFn( key );
      node->mKey = key;
      mSize++;
    }
    return node->mVal;
  }
  void DebugPrint()
  {
    for( int i = 0; i < mCapacity; ++i )
    {
      TacNode* node = &mNodes[ i ];
      std::cout << i << " ";
      if( node->mOccupied )
      {
        std::cout << node->mKey << ", ";
        std::cout << node->mVal << ", ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  void Clear()
  {
    for( int i = 0; i < mCapacity; ++i )
    {
      mNodes[ i ] = TacNode();
    }
    mSize = 0;
  }
  int mSize = 0;
  int mCapacity;
  TacNode* mNodes;
  TacHashFn* mHashFn;
};

