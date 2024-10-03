#pragma once

QString IDString(not_null<PeerData*> peer);

rpl::producer<TextWithEntities> IDValue(not_null<PeerData*> peer);

// brazenly stole from ayugram